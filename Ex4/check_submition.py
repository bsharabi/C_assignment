import glob, os , sys
import shutil
import subprocess
import re
import filecmp
passed = 1

def pars_input():
    submission_file = sys.argv[1]
    print(submission_file)
    f= open(submission_file,"r")
    ids = None
    commit = None
    git_rep = None
    for line in f.readlines():
        if re.search(r'\.git', line):
            git_rep = line
            continue
        if re.search(r'\d{9}', line):
            ids = line
            print(line)
            continue
        if re.search(r'.+', line):
            commit = line
            continue
    return git_rep , ids , commit
def run_cmd(cmd , verbos = 1):
    if verbos == 1:
        print("running: " ,cmd)
    try:
        proc = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE , stderr=subprocess.PIPE)
        proc.wait()
        if proc.returncode != 0:
           raise Exception(" failed p.returncode= " + str(proc.returncode))
    except Exception as inst:
        print("command failed")
        print(inst)
        raise Exception(" failed p.returncode= " + str(proc.returncode))
        


def test_extra_compilation(target):
    global passed
    run_cmd("make " + target + " > compilation_out.txt")
    f = open("compilation_out.txt" , 'r')
    lines = f.readlines()
    if len(lines) > 1 or "gcc " in lines[0] or "ar " in lines[0] :
        print("unneeded recompilation happand for target " ,target) 
        passed = 0
    run_cmd("rm compilation_out.txt" , 0)
    
    
def test_memory(prog , input_f ):
    global passed
    try:
        run_cmd("valgrind --leak-check=full --error-exitcode=1 ./%s < %s > /dev/null"%(prog ,input_f ))
    except Exception as inst:
        print("valgrind failed on input %s"%(input_f) )
        passed = 0

def test_output_vs_expected(prog , input_f , expected_f):
    global passed
    run_cmd("./%s < %s > tmp_out.txt"%(prog ,input_f ))
    if not filecmp.cmp('tmp_out.txt',expected_f ):
        print("difference found in ./%s < %s vs "%(prog ,input_f) ,expected_f)
        passed = 0
        run_cmd("cat tmp_out.txt")
        run_cmd("cat " + expected_f )
    run_cmd("rm tmp_out.txt" , 0)
    
def run_tests():
    print("running tests")   

    test_output_vs_expected("graph" , "../inputs/input1.txt" , "../outputs/output1.txt")
    test_output_vs_expected("graph" , "../inputs/input2.txt" , "../outputs/output2.txt")
    test_output_vs_expected("graph" , "../inputs/input3.txt" , "../outputs/output3.txt")
    test_output_vs_expected("graph" , "../inputs/input4.txt" , "../outputs/output4.txt")
    test_output_vs_expected("graph" , "../inputs/input5.txt" , "../outputs/output5.txt")
    
    test_memory("graph" , "../inputs/input1.txt" )
    test_memory("graph" , "../inputs/input2.txt" )

def main():
    git_rep , ids,  commit = pars_input()
    print ("your git repository is: " + git_rep)
    print ("your ids are: " + ids)
    print ("your commit is: " + commit)

    print("cloning your git: " + git_rep)
    run_cmd("git clone " + git_rep )

    try:
        match = re.search(r'([\w-]+)\.git', git_rep)
        dir = match.group(1)
        print("changing folder to: " + dir)
        os.chdir(dir)
    except Exception as inst:
        print("go into you git dir failed")
        print(inst)
        exit(1)
    
    print("checking out you commit: " + commit)
    run_cmd("git checkout " + commit)
        

    print("compiling with make all")
    run_cmd("make all")

    run_tests()
    
    if passed == 1:
        print("You have PASSED the initial checks.")
    else:
        print("You have FAILED the initial checks. go fix your code.")
    


if __name__ == "__main__":
    main()
