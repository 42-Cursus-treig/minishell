FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y \
    gcc \
    make \
    libreadline-dev \
    nodejs \
    npm \
    python3 \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN cd server && npm install

RUN make

EXPOSE 3001

CMD ["node", "server/index.js"]