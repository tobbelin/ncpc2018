import random
import math

MAX_M = 25
MAX_N = 25
MAX_MN = 100

case_no = 0


def add_case(m, n, case_name = ''):
    if m >= 2 and n >= 2 and m <= MAX_M and n <= MAX_N:
        global case_no
        case_no += 1
        file_name = '%02d' % case_no
        if case_name:
            file_name = file_name + '-' + case_name
        file_name += '.in'

        with open(file_name, "wt") as f:
            f.write('%d %d\n' % (n, m))


def main():
    random.seed(0)

    add_case(2, 2, "small")
    add_case(2, 3, "small")
    add_case(3, 2, "small")
    add_case(3, 3, "small")
    add_case(4, 3, "small")
    add_case(4, 4, "small")
    add_case(5, 4, "small")
    add_case(5, 5, "small")

    m = MAX_M - 1
    n = int(math.floor(MAX_MN / m))
    add_case(m, n, "large")
    add_case(m, n - 1, "large")
    add_case(m - 1, n, "large")
    add_case(m - 1, n - 1, "large")

    n = MAX_N - 1
    m = int(math.floor(MAX_MN / n))
    add_case(m, n, "large")
    add_case(m, n - 1, "large")
    add_case(m - 1, n, "large")
    add_case(m - 1, n - 1, "large")

    n = int(math.floor(math.sqrt(MAX_MN)))
    m = int(math.floor(MAX_MN / n))
    add_case(m, n, "square")

    cnt = 0
    while cnt < 10:
        m = random.randint(2, MAX_M)
        n = random.randint(2, MAX_N)
        if m * n > MAX_MN:
            continue
        add_case(m, n, "random")
        cnt += 1


if __name__ == '__main__':
    main()
