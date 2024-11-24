import random
import subprocess

file_name = "tcat.txt"
file_basic_name = "gentest"
log_file = "testlog.txt"

standard_set = [
    ["test.txt", 0],
    ["test1.txt", 1]]
#     ["test11.txt", 2],
#     ["test12.txt", 2],
#     ["test21.txt", 2],
#     ["test111.txt", 3],
#     ["test123.txt", 3],
#     ["test132.txt", 3],
#     ["test213.txt", 3],
#     ["test231.txt", 3],
#     ["test312.txt", 3],
#     ["test321.txt", 3]
# ]

# ------------------------------------------
# --------Генерация файла и ответов---------
# ------------------------------------------

def generate_test(file_name, count, min_value, max_value):
    test_file = open(file_name, "w")

    for i in range(count):
        test_file.write("Cat")
        test_file.write(" ")
        
        test_file.write(str(random.randint(min_value, max_value)))
        test_file.write("\n")

    test_file.close()

from tree import Tree

def get_answers(file_name):
    test_tree = Tree()
    test_tree.read_from_file(file_name)
    #print(test_tree.nodes)
    #print(test_tree.links)
    #print(test_tree.vertices_levels())

    if test_tree.size() == 0:
        return [0, 0, 0, 0, 0]

    answers = [0, 0, 0, 0, 0]
    answers[0] = test_tree.count_leaves()
    answers[1] = test_tree.depth()
    answers[2] = test_tree.max_level_size()
    answers[3] = test_tree.depths_difference()
    answers[4] = test_tree.count_with_one_child()

    return answers

# -----------------------
# --------Запуск---------
# -----------------------

def create_command(valgrind_status: bool, prec: int, file_name: str) -> list:
    command = []
    
    if valgrind_status:
        command += ["valgrind"]

    command += ["./a.out"]
    command += [str(prec), file_name]

    return command

def process_test(tasks_number: int, valgrind_status: bool, 
                    precision: int, file_name: str):
    command = create_command(valgrind_status, precision, file_name)
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
        answers = []
        return [output, answers, memory_status]

    pos = 0
    answers = [0] * tasks_number
    for i in range(tasks_number):
        pos = out_data.index("Task", pos)
        answers[i] = int(out_data[pos + 5])
        pos += 1

    return [output, answers, memory_status] 

def run_test(test_number: int, tasks_number: int, valgrind_status: bool, 
                    precision: int, file_name: str, size : int, log_file, only_log : bool):
    processing = process_test(tasks_number, valgrind_status, precision, file_name)
    log_result(test_number, size, valgrind_status, file_name, processing, log_file)
    if not(only_log):
        print_result(test_number, size, valgrind_status, file_name, processing)

def check_test(test_number: int, tasks_number: int, valgrind_status: bool, 
                    precision: int, file_name: str, size : int, log_file, only_log : bool):
    processing = process_test(tasks_number, valgrind_status, precision, file_name)

    log_checked_result(test_number, tasks_number, size, valgrind_status, file_name, processing, log_file)
    if not(only_log):
        print_checked_result(test_number, tasks_number, size, valgrind_status, file_name, processing)

# ------------------------
# --------Печать----------
# ------------------------

def print_result(test_number, size, valgrind_status, file_name, processing):
    print("Test № " + str(test_number).ljust(5) + " ", end = "")
    print(file_name.ljust(15) + " ", end="")
    print("Len: " + str(size).ljust(6) + " ", end="")
    
    if valgrind_status:
        memory_status = processing[2]
        if memory_status == "Good!":
            print("Memory: Good! ", end="")
        else:
            print("Memory: Leaks or SF! ", end="")

    if processing[1] == []:
        print("Incorrect file!")
        return

    print("Answers = " + str(processing[1]).ljust(30))
    
def log_result(test_number, size, valgrind_status, file_name, processing, log_file):
    log_file.write("Test № " + str(test_number).ljust(5) + " ")
    log_file.write(file_name.ljust(15) + " ")
    log_file.write("Len: " + str(size).ljust(5) + " ")

    if valgrind_status:
        memory_status = processing[2]
        if memory_status == "Good!":
            log_file.write("Memory: Good! ")
        else:
            log_file.write("Memory: Leaks or SF! ")
            log_file.write(processing[0].stderr.decode("utf-8"))

    if processing[1] == []:
        log_file.write("Incorrect file!")
        return

    log_file.write("Answers = " + str(processing[1]).ljust(30) + "\n")

# ------------------------------------
# --------Печать с проверкой----------
# ------------------------------------

def print_checked_result(test_number, tasks_number, size, valgrind_status, 
                        file_name, processing):
    print("Test № " + str(test_number).ljust(5) + " ", end = "")
    print(file_name.ljust(15) + " ", end="")
    print("Len: " + str(size).ljust(6) + " ", end="")
    
    if valgrind_status:
        memory_status = processing[2]
        if memory_status == "Good!":
            print("Memory: Good! ", end="")
        else:
            print("Memory: Leaks or SF! ", end="")

    if processing[1] == []:
        print("Incorrect file!")
        return
    print()

    correct_answers = get_answers(file_name)
    for i in range(tasks_number):
        print("Task = " + str(i + 1) + ": Your answer = " + str(processing[1][i]).ljust(3) + 
              " Correct answer = " + str(correct_answers[i]).ljust(3) + " ", end="")
        if processing[1][i] == correct_answers[i]:
            print("OK!")
        else:
            print("Wrong Answer!")
    
def log_checked_result(test_number, tasks_number, size, valgrind_status, 
                        file_name, processing, log_file):
    log_file.write("Test № " + str(test_number).ljust(5) + " ")
    log_file.write(file_name.ljust(15) + " ")
    log_file.write("Len: " + str(size).ljust(5) + " ")

    if valgrind_status:
        memory_status = processing[2]
        if memory_status == "Good!":
            log_file.write("Memory: Good! ")
        else:
            log_file.write("Memory: Leaks or SF! ")
            log_file.write(processing[0].stderr.decode("utf-8"))

    if processing[1] == []:
        log_file.write("Incorrect file!")
        return

    correct_answers = get_answers(file_name)
    for i in range(tasks_number):
        log_file.write("Task = " + str(i + 1) + ": Your answer = " + str(processing[1][i]).ljust(3) + 
              " Correct answer = " + str(correct_answers[i]).ljust(3) + " ")
        if processing[1][i] == correct_answers[i]:
            log_file.write("OK!\n")
        else:
            log_file.write("Wrong Answer!\n")
            log_file.write(processing[0].stdout.decode("utf-8"))

# ---------------------------------------
# ------Массовые генерация и запуск------
# ---------------------------------------

def generate_many_tests(min_length, max_length, step, attempts_number, file_basic_name):
    index = 0
    min_value = -10000
    max_value = 10000

    for i in range(min_length, max_length + 1, step):
        for j in range(attempts_number):
            file_name = file_basic_name + str(index) + ".txt"
            generate_test(file_name, i, min_value, max_value)
            index += 1

def run_on_standard_tests(tasks_number, standard_set, valgrind_status, 
                  precision, log_file, only_log):
    print("Standard set test:")
    i = 0
    for unit in standard_set:
        run_test(i, tasks_number, valgrind_status, precision, 
                 unit[0], unit[1], log_file, only_log)
        i += 1

def generate_and_run(tasks_number, min_length, max_length, step, attempts_number,
                      file_basic_name,
                      valgrind_status, precision, log_file, only_log):
    index = 0
    file_basic_name = "gentest"
    min_value = -10000
    max_value = 10000

    print("Generated tests:")
    for i in range(min_length, max_length + 1, step):
        for j in range(attempts_number):
            file_name = file_basic_name + str(index) + ".txt"
            generate_test(file_name, i, min_value, max_value)
            run_test(index, tasks_number, valgrind_status, 
                    precision, file_name, i, log_file, only_log)
            index += 1

def run_on_generated_tests(tasks_number, min_length, max_length, step, attempts_number,
                             file_basic_name, 
                      valgrind_status, precision, log_file, only_log):
    index = 0
    min_value = -10000
    max_value = 10000

    print("Generated tests:")
    for i in range(min_length, max_length + 1, step):
        for j in range(attempts_number):
            file_name = file_basic_name + str(index) + ".txt"
            run_test(index, tasks_number, valgrind_status, 
                    precision, file_name, i, log_file, only_log)
            index += 1

# -------------------------------------------------
# ------Массовая автоматическая проверка-----------
# -------------------------------------------------

def check_on_standard_tests(tasks_number, standard_set, valgrind_status, 
                  precision, log_file, only_log):
    if not(only_log):
        print("Standard set tests:")
    log_file.write("Standard set tests:\n")

    i = 0
    for unit in standard_set:
        check_test(i, tasks_number, valgrind_status, precision, 
                 unit[0], unit[1], log_file, only_log)
        i += 1

def check_on_generated_tests(tasks_number, min_length, max_length, step, attempts_number,
                             file_basic_name, 
                      valgrind_status, precision, log_file, only_log):
    index = 0
    min_value = -10000
    max_value = 10000

    print("Generated tests:")
    for i in range(min_length, max_length + 1, step):
        for j in range(attempts_number):
            file_name = file_basic_name + str(index) + ".txt"
            check_test(index, tasks_number, valgrind_status, 
                    precision, file_name, i, log_file, only_log)
            index += 1

# -------------------------------------
# ----------Для пользователя-----------
# -------------------------------------

min_length = 1
step = 1
max_length = 10
attempts_number = 3
use_valgrind = True 
precision = 8

tasks_number = 5

remake = False

if remake:
    print(subprocess.check_output(["make", "clean"]).decode("utf-8"))
    print(subprocess.check_output(["make"]).decode("utf-8"))

generate_tests = False
check = True

if generate_tests:
    generate_many_tests(min_length, max_length, step, attempts_number, file_basic_name)

only_log = False
log = open(log_file, "w")

if check:
    check_on_standard_tests(tasks_number, standard_set, use_valgrind, precision, log, only_log)
    check_on_generated_tests(tasks_number, min_length, max_length, step, attempts_number, 
                                file_basic_name, use_valgrind, precision, log, only_log)
else:
    run_on_standard_tests(tasks_number, standard_set, use_valgrind, precision, log, only_log)
    run_on_generated_tests(tasks_number, min_length, max_length, step, attempts_number, 
                                file_basic_name, use_valgrind, precision, log, only_log)

log.close()