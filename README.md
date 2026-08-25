# HTTP Server

A small HTTP server written in C using Winsock.

This project started as a networking/systems programming exercise to understand how an HTTP server works at a lower level instead of relying on an HTTP framework.

## Current Features

- TCP socket server using Winsock
- Listens on port `8081`
- Multiple clients handled using `select()`
- Request accumulation until the HTTP header terminator (`\r\n\r\n`) is received
- Basic HTTP request-line parsing
- Static file serving
- `GET` and `HEAD` recognized as allowed methods
- `POST`, `PUT`, and `DELETE` currently return `405 Method Not Allowed`
- Unknown methods currently return `400 Bad Request`
- `404 Not Found` handling with an error page
- MIME type detection from the requested file extension
- MIME type lookup table
- Binary-safe file reading using `fopen(..., "rb")` and `fread()`
- `Content-Length` generation
- Basic HTTP response construction

## Request Flow

```text
Client
  |
  v
accept()
  |
  v
recv()
  |
  v
Request accumulator
  |
  v
Detect \r\n\r\n
  |
  v
parser()
  |
  +---- method
  +---- path
  +---- HTTP version
  |
  v
doc_prep()
  |
  +---- validate method
  +---- locate file
  +---- read file
  +---- determine response state
  |
  v
mime_extract()
  |
  v
mime_lookup()
  |
  v
response_builder()
  |
  +---- status line
  +---- Content-Type
  +---- Content-Length
  |
  v
send()
  |
  +---- HTTP headers
  +---- response body
```

## Project Structure

The project is divided into several components:

- **Server loop** — Winsock initialization, socket setup, client management, `select()`, receiving requests and sending responses.
- **`parser`** — extracts the HTTP method, path and version from the request.
- **`doc_prep`** — determines the resource to serve, handles basic request status decisions, and reads the requested file into the response payload.
- **`mime_chk`** — extracts the file extension and maps it to a MIME type.
- **`response_build`** — constructs the HTTP response headers.

## Supported Responses

| Situation | Response |
|---|---|
| Existing resource requested with `GET` | `200 OK` |
| Existing resource requested with `HEAD` | `200 OK` |
| Resource does not exist | `404 Not Found` |
| Unknown/invalid method | `400 Bad Request` |
| `POST`, `PUT`, or `DELETE` | `405 Method Not Allowed` |
| Unexpected internal condition | `500 Internal Server Error` |

## Building

This project currently targets Windows and uses Winsock.

With a MinGW/MSYS2-style environment, a build can look like:

```bash
gcc *.c -o http_server.exe -lws2_32
```

The exact command may need to be adjusted depending on the project layout.

## Running

Place the files you want to serve in the server's working directory.

The root request:

```text
GET /
```

is mapped to:

```text
index.html
```

Start the server and connect to:

```text
http://localhost:8081/
```

You can also test it using `curl`.

## What I Learned

The main purpose of this project was not to create a production-ready HTTP implementation. It was to understand the pieces underneath an HTTP server.

Topics covered include:

- TCP sockets
- Winsock
- `bind()`, `listen()`, `accept()`
- `select()` and client multiplexing
- TCP byte streams
- Request buffering
- HTTP request structure
- HTTP status codes
- HTTP headers
- MIME types
- File I/O
- Binary data handling
- Buffer management
- Client state management
- Separating a C program into multiple modules

## Known Limitations

This is a learning project rather than a production HTTP server. Some areas are intentionally simplified:

- `send()` currently assumes the requested data is sent in one call.
- Response buffers have fixed capacity.
- Request and path handling need stronger bounds checking.
- `sprintf()` should eventually be replaced with bounded alternatives.
- Request termination detection can be made more robust.
- `HEAD` currently follows the normal response-body path and should eventually return headers without a body.
- Persistent connections are not fully implemented.
- More HTTP methods could be implemented later.
- Path traversal/security checks are not currently implemented.
- Memory cleanup and shutdown handling could be improved.
- HTTP protocol support is intentionally limited to a small subset.

## Why I Built It

The goal was to build an HTTP server from the lower level up and understand what happens between a TCP connection and an actual HTTP response.

Rather than using an existing HTTP framework, the project deliberately handles the socket, request parsing, file reading, MIME detection, response construction, and transmission itself.
