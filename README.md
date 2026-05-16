# Search Algorithms

A collection of classical search algorithms implemented in modern C++.

This project is intended for:
- learning and educational purposes,
- algorithm visualization and experimentation,
- benchmarking and comparison of search strategies,
- reusable reference implementations.

---

## Features

Currently implemented / planned algorithms may include:

- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Dijkstra
- A*
- Greedy Best-First Search
- Bidirectional Search
- Flood Fill
- Heuristic-based pathfinding

Additional algorithms and optimizations may be added over time.

---

## Project Goals

The main goals of this repository are:

- clean and understandable implementations,
- modern C++ design,
- separation of algorithm and visualization logic,
- extensibility for experimentation,
- educational readability,
- reproducible behavior.

---

## Requirements

### Compiler

A C++20 compatible compiler is recommended.

Examples:
- GCC 13+
- Clang 17+
- MSVC 2022+

### Build System

- CMake 3.16 or newer

---

## Project Structure

```text
search_algorithms/
├── include/        # Public headers
├── src/            # Source files
├── tests/          # Unit tests
├── docs/           # Documentation
├── build/          # Build output (generated)
└── CMakeLists.txt
```

---

## Documentation

The project may use Doxygen for API documentation generation.

Example:

```bash
doxygen Doxyfile
```

Generated documentation is typically located in:

```text
docs/html/
```

---

## Testing

If Google Test is configured:

```bash
ctest --test-dir build
```

or:

```bash
./build/test_search_algorithms
```

---

## Code Style

General conventions:

- modern C++20 style,
- RAII principles,
- const correctness,
- minimal raw pointer ownership,
- clear naming conventions,
- modular design.

---

## Disclaimer

This software is provided for educational and experimental purposes.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT.

Use at your own risk.

---

## License

This project is licensed under the MIT License.

See the LICENSE file for details.

---

## Contributing

Contributions, issues, and suggestions are welcome.

Please ensure:
- readable code,
- consistent formatting,
- reasonable documentation,
- successful compilation before submitting changes.

---

## Author

Created and maintained by Christoph Kolhoff.

GitHub:
https://github.com/chk1990
