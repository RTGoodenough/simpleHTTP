
  

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

Run `./simpleHTTP`
  
- Currently the server only runs on port `9000`, configuration is a planned addition
  

---

# Routing

  

  

**Routing is file based.**

  
  

Meaning pages are placed in the `routes/` directory, for child routes add them to a directory under `routes/`

  

  

ex. The route `/example/route.html` will use the file at `/routes/example/route.html`

  

**Special Paths:**

- The base route `/` will be responded to with `/routes/index.html`

  

- Any requests for routes/pages that don't exist will be responded to with `NotFound.html`