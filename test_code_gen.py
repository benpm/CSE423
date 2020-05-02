import os
import pathlib
import subprocess
import filecmp

red = '\033[91m'
stop = '\033[0m'
green = '\033[92m'

def compile_sc64(path, silent=True):
    failed = 0
    failed += run_command(f"./build/sc64 -Sl {path} tmpSC64.s > tmpSC64.s", stdout=None)
    failed += run_command("gcc tmpSC64.s -o tmpSC64")
    print(f"{red} FAILED!{stop}" if failed != 0 else f"{green} DONE!{stop}")
    return failed

def run_command(cmdstr, silent=True, stdout=subprocess.DEVNULL):
    process = subprocess.Popen(cmdstr, shell=True, stdout=stdout, stderr=subprocess.DEVNULL)
    process.wait()

    if silent == True:
        return process.returncode

    print(f"{red} FAILED!{stop}" if process.returncode != 0 else f"{green} DONE!{stop}")
    return process.returncode

def test_file(path):
    print("\n############################" + "#" * 20 + "############################")
    print(f"# {os.path.basename(path):^72} #")
    print("############################" + "#" * 20 + "############################")
    print(f"# Compiling with GCC....", end="")
    gccres = run_command(f"gcc {path} -o tmpGCC", silent=False)

    print(f"# Compiling with SC64...", end="")
    sc64res = compile_sc64(path)

    if gccres != 0 or sc64res != 0:
        print(f"# {red}Test failed during compilation!!{stop}")
        run_command("rm tmpGCC tmpSC64 tmpSC64.s tmpSC64.o")
        return
    
    gccres  = run_command("./tmpGCC > tmpgcc.txt")
    sc64res = run_command("./tmpSC64 > tmpsc64.txt")
    diffres = run_command("diff tmpgcc.txt tmpsc64.txt >/dev/null")
    if (diffres != 0):
        print(f"# {red}Test failed on PRINTF OUTPUT!!{stop}")
    else:
        print(f"# {green}Test passed on PRINTF OUTPUT!!{stop}") 

    if (gccres != sc64res):
        print(f"# {red}Test failed on RETURN VALUE!!{stop}")
    else:
        print(f"# {green}Test passed on RETURN VALUE!!{stop}") 

    if (gccres != sc64res):
        print(f"GCC: {gccres} | Us: {sc64res}")
    if (diffres != 0):
        print(f"# ------------------------- Left: GCC | Right: Us --------------------------")
        run_command("diff tmpgcc.txt tmpsc64.txt -y -W 80", stdout=None)

    run_command("rm tmpGCC tmpSC64 tmpSC64.s tmpgcc.txt tmpsc64.txt")
    print("############################" + "#" * 20 + "############################")



def main():
    examples_dir = "./examples/"
    test_files = [str(f) for f in pathlib.Path(examples_dir).glob('**/*') if ".c" in str(f) and ".csv" not in str(f)]

    for f in test_files:
        test_file(f)

if __name__ == "__main__":
    main()