cmd_len  = 1 # the line of the command
funcs    = 5
func_len = 4 # 4 lines per function
tests    = 4
test_len = cmd_len + funcs * func_len 
tries    = 3
try_len  = tests * test_len

with open('wsl-ub-2004.res', 'r') as res_file:

    lines = res_file.read().split('\n')

    for func in range(funcs):
        
        print(f"Func #{func + 1}")
        print()

        results = [float(0) for x in range(tests)]

        for _try in range(tries): 

            start_of_try = try_len * _try

            for test in range(tests):

                start_of_test = start_of_try + test_len * test

                start_of_func = start_of_test + cmd_len + func_len * func

                func_res = start_of_func + func_len - 2

                results[test] += float(lines[func_res].split(' ')[2])

        for res in results:

            print(res / float(tries))

        print()


        