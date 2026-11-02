#!/bin/bash
set -e
# Make sure you follow this installation procedure beforehand:
# https://confluence.synchrotron-soleil.fr/spaces/TAURUS/pages/193567934/A+Cr%C3%A9er+un+environnement+Conda+depuis+un+r%C3%A9seau+de+contr%C3%B4le
fail() {
	echo "Error: make sure you follow this installation procedure beforehand: https://confluence.synchrotron-soleil.fr/spaces/TAURUS/pages/193567934/A+Cr%C3%A9er+un+environnement+Conda+depuis+un+r%C3%A9seau+de+contr%C3%B4le" >&2
	exit 1
}

source /usr/Local/miniforge3/miniforge3rc || fail
conda activate taurus_test || fail
python live_image_widget.py "$@"