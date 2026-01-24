# Free Noise Map (FNM)

<p align="center">
  <img src="code/ui/icons/app_icon.png" width="150">
</p>

**Free Noise Map (FNM)** is a multi-platform, free, and open-source environmental noise modelling software. It targets major desktop and mobile operating systems, as well as the web, providing an accessible tool for acoustic simulation.

## 🚀 Live Demo
Try out FNM directly in your browser (limited functionality):  
👉 **[Launch FNM Web Demo](https://christian-mv.github.io/Free_Noise_Map_Demo/FreeNoiseMap.html)**

---

## ✨ Features
*   **Acoustic Standards**: Currently implements **ISO 9613-2** for attenuation calculations.
*   **Noise Sources**: Support for Point Sources, Line Sources, and Multi-line Sources.
*   **Barriers**: Modeling of acoustic barriers and diffraction.
*   **Visualization**:
    *   Receiver grids with configurable resolution.
    *   Noise contour maps (Heatmaps).
*   **Cross-Platform**: Runs natively on Linux, Windows, macOS, Android, and iOS.

## 🖥️ Supported Platforms

| Platform | Status |
| :--- | :--- |
| **Desktop** | Linux, Windows, macOS |
| **Mobile** | Android, iOS |
| **Web** | Chrome, Firefox, Opera, Safari, Edge (via WebAssembly) |

---

## 🛠️ Building from Source

FNM is developed in **C++20** using the **Qt 6** framework.

### Prerequisites
*   **C++ Compiler**: Compatible with C++20 (GCC, Clang, MSVC).
*   **Qt 6**: Core, Gui, and Widgets modules.
*   **CMake**: Version 3.16 or higher.

### Build Steps
1.  **Clone the repository**:
    ```bash
    git clone https://github.com/christian-mv/Free-Noise-Map.git
    cd Free-Noise-Map
    ```

2.  **Create a build directory**:
    ```bash
    mkdir build && cd build
    ```

3.  **Configure with CMake**:
    ```bash
    cmake ..
    ```
    *Note: You may need to provide the path to your Qt installation if it's not in your system path (e.g., `-DCMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/gcc_64`).*

4.  **Build**:
    ```bash
    cmake --build .
    ```

---

## 🗺️ Roadmap

### Stage 1 (Current Focus)
- [x] ISO 9613-2 implementation.
- [x] Basic Qt User Interface.
- [ ] Integration with web map services (Google Maps, OpenStreetMap).

### Stage 2 (Planned)
- [ ] **CNOSSOS-EU** calculation method implementation.
- [ ] GIS and CAD file support (DXF, SHP) via GDAL library integration.

---

## 📸 Gallery

### User Interface (Linux)
![Linux](https://raw.githubusercontent.com/christian-mv/Free-Noise-Map/master/screenshoots/gui_on_Linux.png)

---

## 🤝 Contributing
FNM is in its early stages of development. Contributions, bug reports, and feature requests are welcome!

## 📄 License
This project is licensed under the terms of the LICENSE file located in the root directory.