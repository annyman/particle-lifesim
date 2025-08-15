# Maintainer: annyman <annyman.81194@protonmail.com>
pkgname=particle-lifesim
pkgver=0.1.1
pkgtag="gui"
pkgrel=1
pkgdesc="A particle-based artificial life simulation, implemented with raylib and C++"
arch=('x86_64')
url="https://github.com/annyman/particle-lifesim"
license=('MIT')
depends=('raylib' 'raygui')
makedepends=('meson' 'ninja' 'gcc')
source=("$url/archive/refs/tags/${pkgtag}.tar.gz")
sha256sums=('da6307293714273ccf0cd0fb05c735b777e39a02d46b711d08ccf9d265dcc7d2')

build() {
    cd "${pkgname}-${pkgtag}"
    arch-meson . build
    meson compile -C build
}

package() {
    cd "${pkgname}-${pkgtag}"
    meson install -C build --destdir="$pkgdir"
    install -Dm644 LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}
