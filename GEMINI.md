# Free Noise Map - Coding Standards (Gemini)

This document outlines the modern and professional coding standards adopted for the Free Noise Map project. All future modifications should adhere to these rules.

## 1. Syntax & Style
*   **Global Scope Resolution Operator (`::`):** Do not use the `::` prefix for classes or functions (e.g., `::QGraphicsView`) unless strictly required for constructor initialization lists or to resolve a legitimate ambiguity that cannot be handled via namespaces.
*   **Type Aliases:** Prefer `using AliasName = Type;` over `#define ALIAS_NAME Type`.
*   **Constants:** Use `constexpr` or `const` variables instead of `#define` macros for constant values.

## 2. Architecture
*   **Separation of Concerns:** Keep the `core` library strictly independent of the UI framework (Qt). Core logic should handle data and physics, while the UI handles rendering.
*   **File Symmetry:** Every header file (`.h`) should have a corresponding implementation file (`.cpp`), unless the class is a pure interface or extremely simple (e.g., a simple POD struct).

## 3. Memory Safety
*   **Smart Pointers:** Avoid raw `new` and `delete`. Use `std::unique_ptr` for exclusive ownership and `std::shared_ptr` only when shared ownership is strictly necessary.
*   **Value Semantics:** Prefer storing objects by value in containers (e.g., `std::vector<Point>`) rather than by pointer to improve memory safety and cache locality.

## 4. Performance
*   **Linear Algebra:** Use the **Eigen** library for all vector, matrix, and geometric calculations.
*   **Optimizations:** Ensure the build system (CMake) is configured with high-performance flags (`-O3`, `-march=native`) for Release builds.
*   **Efficient Rendering:** Avoid excessive draw calls. Prefer pixel manipulation or batching when rendering large data sets like noise grids.

## 5. Build System
*   **CMake:** Maintain clean CMake files. Expose external dependencies like Eigen as interface libraries.
