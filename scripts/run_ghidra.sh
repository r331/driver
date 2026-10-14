set -e
cd /workspace/tools
[ -d ghidra_12.1.4_PUBLIC ] || { curl -sSL -o g.zip https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_12.1.4_build/ghidra_12.1.4_PUBLIC_20260921.zip; python3 -m zipfile -e g.zip . ; rm g.zip; chmod +x ghidra_12.1.4_PUBLIC/support/* ghidra_12.1.4_PUBLIC/GPL/*/os/*/* 2>/dev/null || true; }
mkdir -p /tmp/gproj
ghidra_12.1.4_PUBLIC/support/analyzeHeadless /tmp/gproj Driver -import /workspace/projects/ce1b1d6d-abf1-4bda-ab0c-56fb1670a4a3/input/game/Program_Executable_Files/Game.exe -overwrite -scriptPath /workspace/projects/ce1b1d6d-abf1-4bda-ab0c-56fb1670a4a3/scripts -postScript ExportAll.java /workspace/projects/ce1b1d6d-abf1-4bda-ab0c-56fb1670a4a3/out -max-cpu 2 > /workspace/projects/ce1b1d6d-abf1-4bda-ab0c-56fb1670a4a3/out/ghidra.log 2>&1
tail -5 /workspace/projects/ce1b1d6d-abf1-4bda-ab0c-56fb1670a4a3/out/ghidra.log
