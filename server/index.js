const { execSync } = require('child_process');
const http  = require('http');
const { WebSocketServer } = require('ws');
const pty   = require('node-pty');
const path  = require('path');
const os    = require('os');
const fs    = require('fs');

const PORT   = process.env.PORT || 3001;
const BINARY = path.resolve(__dirname, '..', 'minishell');

/* ── Compile minishell au démarrage ── */
try {
  execSync('make -C ' + path.resolve(__dirname, '..'), { stdio: 'inherit' });
  console.log('✓ minishell compiled');
} catch (e) {
  console.error('✗ make failed:', e.message);
  process.exit(1);
}

/* ── Serveur HTTP (health check Railway) ── */
const httpServer = http.createServer((req, res) => {
  res.writeHead(200, { 'Content-Type': 'text/plain' });
  res.end('minishell server OK\n');
});

/* ── WebSocket ── */
const wss = new WebSocketServer({ server: httpServer });

wss.on('connection', (ws) => {
  console.log('New connection');

  const tmpDir = os.tmpdir() + '/minishell-' + Date.now();
  fs.mkdirSync(tmpDir, { recursive: true });

  /* Spawn via PTY — readline fonctionne correctement */
  const shell = pty.spawn(BINARY, [], {
    name: 'xterm-color',
    cols: 120,
    rows: 30,
    cwd:  tmpDir,
    env:  { ...process.env, TERM: 'xterm-color', HOME: tmpDir },
  });

  /* Timeout 5 minutes */
  let timeout = setTimeout(() => shell.kill(), 5 * 60 * 1000);
  const resetTimeout = () => {
    clearTimeout(timeout);
    timeout = setTimeout(() => shell.kill(), 5 * 60 * 1000);
  };

  /* PTY output → client */
  shell.onData(data => {
    if (ws.readyState === ws.OPEN)
      ws.send(JSON.stringify({ type: 'stdout', data }));
  });

  shell.onExit(({ exitCode }) => {
    clearTimeout(timeout);
    if (ws.readyState === ws.OPEN)
      ws.send(JSON.stringify({ type: 'exit', code: exitCode }));
    ws.close();
    fs.rmSync(tmpDir, { recursive: true, force: true });
  });

  /* Client → PTY stdin */
  ws.on('message', msg => {
    try {
      const { data } = JSON.parse(msg.toString());
      if (data) { resetTimeout(); shell.write(data); }
    } catch {}
  });

  ws.on('close', () => {
    clearTimeout(timeout);
    try { shell.kill(); } catch {}
    fs.rmSync(tmpDir, { recursive: true, force: true });
  });

  ws.on('error', () => {
    try { shell.kill(); } catch {}
  });
});

httpServer.listen(PORT, () => {
  console.log(`minishell server listening on port ${PORT}`);
});