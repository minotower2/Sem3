import subprocess
from tree import Tree

def create_command(valgrind_status: bool, prec: int, file_name: str, string: str = "t", value: int = 1) -> list:
    command = []
    
    if valgrind_status:
        command += ["valgrind"]
    
    command += [f"./a.out"]
    command += [str(prec), file_name]
    command += [str(value)]

    return command

def process_test(task_count: int, valgrind_status: bool, 
                    precision: int, file_name: str, string: str, value: int = 0):
    command = create_command(valgrind_status, precision, file_name, string, value)
    output = subprocess.run(command, capture_output=True)

    err = output.stderr.decode("utf-8")
    if err == "":
        memory_status = ""
    elif ("no leaks are possible" in err):
        memory_status = "Good!"
    else:
        memory_status = "Bad!"

    out = output.stdout.decode("utf-8")
    out_data = out.split()
    if not("Result" in out_data):
        return [output, memory_status, [], []]
    
    pos = -1
    st_answers = []
    for i in range(task_count):
        pos = out_data.index("Result", pos + 1)
        st_answers += [int(out_data[pos + 2])]
    
    lst_answers = []
    for i in range(task_count):
        pos = out_data.index("Result", pos + 1)
        lst_answers += [int(out_data[pos + 2])]

    return [output, memory_status, st_answers, lst_answers]
    
def check(task_count, file_name, processing, string = "t", k = 0, print_tree = False,
          reference_answers = [], reference_check = False):
    st_result = "OK"
    lst_result = "OK"

    st_tr = Tree()
    st_tr.read_from_file(file_name)

    if print_tree:
        st_tr.print_tree()

    st_correct_answer = st_tr.summary()

    if st_correct_answer == processing[2] and \
        (not(reference_check) or st_correct_answer == reference_answers[0]):
        st_result = "OK"
    else:
        st_result = "Wrong Ans"


    lst_tr = Tree()
    lst_tr.read_from_file(file_name, k)

    if print_tree:
        lst_tr.print_tree()
    
    lst_correct_answer = lst_tr.summary()
    if lst_correct_answer == processing[3] and \
        (not(reference_check) or lst_correct_answer == reference_answers[1]):
        lst_result = "OK"
    else:
        lst_result = "Wrong Ans"

    return [st_result, st_correct_answer, lst_result, lst_correct_answer]
    
