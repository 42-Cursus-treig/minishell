const { execSync, spawn } = require('child_process');
const http  = require('http');
const { WebSocketServer } = require('ws');
const path  = require('path');
const os    = require('os');

const PORT    = process.env.PORT || 3001;
const BINARY  = path.resolve(__dirname, '..', 'minishell');

try {
  execSync('make -C ' + path.resolve(__dirname, '..'), { stdio: 'inherit' });
  console.log('✓ minishell compiled');
} catch (e) {
  console.error('✗ make failed:', e.message);
  process.exit(1);
}

const httpServer = http.createServer((req, res) => {
  res.writeHead(200, { 'Content-Type': 'text/plain' });
  res.end('minishell server OK\n');
});

const wss = new WebSocketServer({ server: httpServer });

wss.on('connection', (ws, req) => {
  console.log('New connection from', req.socket.remoteAddress);

  const tmpDir = os.tmpdir() + '/minishell-' + Date.now();
  require('fs').mkdirSync(tmpDir, { recursive: true });

  const shell = spawn(BINARY, [], {
    cwd:   tmpDir,
    env:   { ...process.env, TERM: 'xterm', HOME: tmpDir },
    stdio: ['pipe', 'pipe', 'pipe'],
  });

  let timeout = setTimeout(() => shell.kill(), 5 * 60 * 1000);
  const resetTimeout = () => {
    clearTimeout(timeout);
    timeout = setTimeout(() => shell.kill(), 5 * 60 * 1000);
  };

  shell.stdout.on('data', data => {
    if (ws.readyState === ws.OPEN)
      ws.send(JSON.stringify({ type: 'stdout', data: data.toString() }));
  });

  shell.stderr.on('data', data => {
    if (ws.readyState === ws.OPEN)
      ws.send(JSON.stringify({ type: 'stderr', data: data.toString() }));
  });

  shell.on('close', code => {
    clearTimeout(timeout);
    if (ws.readyState === ws.OPEN)
      ws.send(JSON.stringify({ type: 'exit', code }));
    ws.close();
    require('fs').rmSync(tmpDir, { recursive: true, force: true });
  });

  ws.on('message', msg => {
    try {
      const { data } = JSON.parse(msg.toString());
      if (data && !shell.killed) {
        resetTimeout();
        shell.stdin.write(data);
      }
    } catch {}
  });

  ws.on('close', () => {
    clearTimeout(timeout);
    if (!shell.killed) shell.kill();
    require('fs').rmSync(tmpDir, { recursive: true, force: true });
  });

  ws.on('error', () => shell.kill());
});

httpServer.listen(PORT, () => {
  console.log(`minishell server listening on port ${PORT}`);
});