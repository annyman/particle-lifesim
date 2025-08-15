Gotcha ✅ — I remember the repo (your **particle-lifesim** project), and we already talked about the `.pkgbuild` branch idea.
Let’s turn that goal into a **clear execution plan** so tomorrow it’s just plug‑and‑play for you.

***

## **Step‑by‑Step Plan**

### **1. Prepare PKGBUILD**

- Start from the template we discussed earlier for Meson + raylib.
- Point the `source=()` to your GitHub **release tarball**:

```bash
source=("https://github.com/annyman/particle-lifesim/archive/refs/tags/v${pkgver}.tar.gz")
```

- Run:

```bash
makepkg --printsrcinfo > .SRCINFO
```

This generates the `.SRCINFO`.

***

### **2. Create the Packaging Branch**

From your local repo (`main` branch checked out):

```bash
git checkout -b packaging
```


***

### **3. Add Files to Packaging Branch**

Move or copy `PKGBUILD` and `.SRCINFO` into the repo root **on this branch only**:

```bash
git add PKGBUILD .SRCINFO
git commit -m "Add Arch Linux PKGBUILD and .SRCINFO"
git push origin packaging
```


***

### **4. Add Build Instructions to README**

On **main branch** (not packaging branch):

Add an “**Arch Linux Build \& Install**” section:

```markdown
## Build & Install on Arch Linux

You can build this game from source in one command using `makepkg`:

```


# Clone only the packaging branch (contains PKGBUILD and .SRCINFO)

```
git clone --branch packaging https://github.com/annyman/particle-lifesim.git
cd particle-lifesim

makepkg -si
```

This will:
1. Download the source from the latest GitHub release tarball.
2. Build with Meson.
3. Install via pacman.

***

### **5. Workflow for Updating**

When you release a new version:

1. **Update** `pkgver` in PKGBUILD.
2. Update checksum:

```bash
makepkg --printsrcinfo > .SRCINFO
```

3. Commit \& push to `packaging` branch.
4. Tag + publish new release on GitHub so the `source` URL works.

***

### **6. Benefits of This Setup**

- **Source branch** (`main`) stays clean = your game’s code only.
- **Packaging branch** contains minimal files for Arch builds.
- Arch users can install with **one command**.
- You’ve got a reproducible + professional distribution method ready for potential AUR submission.

***

I can prep **a final ready-to-use PKGBUILD** for `particle-lifesim` now so that tomorrow you just:

```bash
makepkg -si
```

Would you like me to make that PKGBUILD specific to **your repo + dependencies** right now? That way, you wake up and it’s just copy-paste.

