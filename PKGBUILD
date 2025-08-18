# Maintainer: annyman <annyman.81194@protonmail.com>
pkgname=particle-lifesim
pkgver=0.1.5
pkgrel=1
pkgdesc="A particle-based artificial life simulation, implemented with raylib and C++"
arch=('x86_64')
url="https://github.com/annyman/particle-lifesim"
license=('MIT')
makedepends=('meson' 'ninja' 'gcc')
depends=('raylib')
source=("$url/archive/refs/tags/v${pkgver}.tar.gz")
sha256sums=('d83675f10e3117ed573dc53e93c100c07bdc9dfaf370601c1b2d1aa57a9d9338')

build() {
    cd "${pkgname}-${pkgver}"
    meson setup build --buildtype debug
    meson compile -C build
}

package() {
    cd "${pkgname}-${pkgver}"
    meson install -C build --destdir="$pkgdir"
    install -Dm644 LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}
