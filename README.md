# 🧬 Particle Life Simulator

A **particle-based artificial life simulation** inspired by [Create Life From a Simple Rule](https://youtu.be/0Kx4Y9TVMGg) by Brainxyz. Watch emergent, life-like patterns and behavior as colorful particles interact through simple attraction and repulsion rules—all brought to life with **raylib**, **raymath**, **raygui**, and a modern build system.

---

## 🌟 What is it?

Simulate a 2D universe where:
- 🟠 Particles move, collide, and interact with unique attraction & repulsion forces.
- 🌐 Multiple species create fascinating, self-organizing structures.
- 🛠️ You can tweak parameters live to explore the world of digital emergence.

This is a raylib-powered spin on Brainxyz’s JS original, built for education, fun, and discovery.

---

## 🚀 Features

- 🔄 Interacting, emergent particle types.
- 🎛️ Live parameter tuning with raygui.
- ⚡ Fast graphics via raylib/raymath.
- 🏗️ [Meson](https://mesonbuild.com/) for effortless builds.
- 💻 Pre-built Windows binaries in [Releases](./releases).

---

## 🛠️ Quick Build

Clone and build:

This project uses the [Meson build system](https://mesonbuild.com/) and supports two build configurations: **debug** and **release**.

Clone the repo and navigate into it

```
git clone https://github.com/annyman/particle-lifesim
cd particle-lifesim
```

Choose one of the build setups and build the project:

```
meson setup build/release --buildtype release
meson compile -C build/release
```
or
```
meson setup build/debug --buildtype debug
meson compile -C build/debug -v
```

> 🪟 **Windows building support is coming soon!**

---

## Releases

Pre-built Windows binaries are available in the [Releases](./releases) section of this repository for easy and immediate use without compilation.

---

## 📦 Dependencies

- [raylib](https://www.raylib.com/) (with raymath)
- [raygui](https://github.com/raysan5/raygui)
- [Meson build system](https://mesonbuild.com/)

---

## 📄 License

MIT

---

## Acknowledgments

- The original concept and inspiration come from Brainxyz’s video "Create Life From a Simple Rule" on YouTube.
- Thanks to raylib and raygui for providing a simple and powerful framework for game and simulation development.

---

✨ **Experiment, play, and uncover new digital life—it's all just particles!**

