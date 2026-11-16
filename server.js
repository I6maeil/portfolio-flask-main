// Import module http
const http = require("http");

// Create server
const server = http.createServer((req, res) => {
  res.writeHead(200, { "Content-Type": "text/plain" });
  res.end("Salam! Hada server dyali b Node.js 😎");
});

// Listen in port 3000
server.listen(3000, () => {
  console.log("Server kaykhdem f http://localhost:3000");
});
