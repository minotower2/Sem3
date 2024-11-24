import random
import subprocess
import sys

if len (sys.argv) == 2 and sys.argv[1] == "-h":
   print ("k[1] p(1) valgrind(0) new test(0) count(1000)")
   sys.exit(0)
argv = [1,1,0,0,1000]
for i in range (len(sys.argv)-1):
   argv[i] = int (sys.argv[i+1])
k, precision, use_valgrind, make_test, count = argv
file_name = "list_of_students.txt"

# --------------------------
# --------Генерация---------
# --------------------------

#make_test = True 
#count = 1000
max_len = 1
min_ascii_symbol = 48
max_ascii_symbol = 57
min_value = 0
max_value = 0

def create_test(file_name, count, max_len, min_ascii_symbol, max_ascii_symbol, min_value, max_value):
    test_file = open(file_name, "w")
    i = 0
    while (i < count):
        curr_len = random.randint(1, max_len)
        s= ""
        for index in range(curr_len):
            s= s +chr(random.randint(min_ascii_symbol, max_ascii_symbol))
        s = s + " "
        j = random.randint (1, count - i)
        match random.randint(1,4):
            case 1:
               s = s +"0"+"\n"
               for _ in range(j):
                  test_file.write(s)
               i = i+j
            case 2:
               for x in range(j):
                  test_file.write(s + str(x) + "\n")
               i = i+j
            case 3:
               for x in range(j):
                  test_file.write(s + str(-x) + "\n")
               i = i+j
            case 4:
               test_file.write (s + "0\n")
               i = i+1

    test_file.close()


# --------------------------
# ------Тестирование--------
# --------------------------

#use_valgrind = True
#precision = 0
first_task = 1
last_task = 8

def create_command(task_number: int, valgrind_status: bool, k : int, prec: int, file_name: str) -> list:
    command = []
    
    if valgrind_status:
        command += ["valgrind"]

    command += ["./a"]
    if task_number < 10:
        command[-1] += "0" + str(task_number) 
    else:
        command[-1] += str(task_number)
    command[-1] += ".out"
    #if (task_number < 6):
    #    command += [str(len), str(prec), "0", file_name]
    command += [str(prec), file_name, str(k)]

    return command




#make_test,use_valgrind, k = [int(i) for i in (input("new test(1/0) valgrind (1/0) k:").split())]



if (make_test):
    create_test(file_name, count, max_len, min_ascii_symbol, max_ascii_symbol, min_value, max_value)
#print(subprocess.check_output(["make", "clean"]).decode("utf-8"))
#print(subprocess.check_output(["make"]).decode("utf-8"))

for i in range(first_task, last_task + 1):
    print(f"task № {i}:")
    command = create_command(i, use_valgrind, k, precision, file_name)
    print(subprocess.check_output(command).decode("utf-8"))
