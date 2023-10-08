
# simpleHTTP

### A simple static HTTP server made in C++.

---

### ! This is a personal project and not meant to be used in any actual capacity !


- I don't mind anyone using it, I would just advise against it

---

# Building & Running

  
### Building:

The server is built through CMake:

Run `cmake -B build .` then `cmake --build build`

### Running:

To run the server:

Run `./simpleHTTP *flags*`

### Flags:

The current flags are:
```
1. -port    // Sets the port the server runs on (required)
2. -routes  // Sets the base directory for pages (required)
3. -threads // Sets the number of threads (optional)
```

**Example:**
```
./simpleHTTP -port=9000 -routes=./routes -threads=4
```
---
# Routing

**Routing is file based.**

Meaning pages are placed in the `*routes*` flag directory, for child routes add them to a directory under `*routes*`

ex. The route `/example/route.html` will use the file at `*routes*/example/route.html`

**Special Paths:**

- The base route `/` will be responded to with `*routes*/index.html`

- Any requests for routes/pages that don't exist will be responded to with `*routes*/NotFound.html`