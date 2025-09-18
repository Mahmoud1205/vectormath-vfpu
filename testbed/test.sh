#!/bin/bash

./build.sh

AskIfWantWindows() {
	while true; do
		read -n1 -r -p "Do you want to emulate using the Windows Emulator? (Y/n): " ans
		echo -e "\nStarting emulator.."
		case "$ans" in
			[Yy])	return 0 ;;
			[Nn])	return 1 ;;
			*)		echo "Please answer y or n." ;;
		esac
	done
}

if make -j13 PRX=0; then
	if AskIfWantWindows; then
		wine ./tools/emu_win/PPSSPPWindows64.exe -d ./bin/Testbed/EBOOT.PBP > /dev/null 2>&1
	else
		# flatpak run org.ppsspp.PPSSPP -d ./bin/Testbed/EBOOT.PBP > psp.log 2>&1
		stdbuf -oL -eL flatpak run org.ppsspp.PPSSPP -d ./bin/Testbed/EBOOT.PBP 2>&1 \
			| grep --line-buffered 'PRINTF' \
			| sed -u -E 's/.*PRINTF\]: [^ ]+ //' \
			| sed -E 's/^(stderr|stdout): //' >&2
	fi

	# grep 'PRINTF' psp.log | sed -E 's/.*PRINTF\]: [^ ]+ //' > psp.tmp && mv psp.tmp psp.log
else
	echo "Error: Compilation failed.."
fi;
