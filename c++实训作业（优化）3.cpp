#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>
#include <chrono>
#include <thread>

// 计算最大公约数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 生成满足要求的数组，控制数字不超过 1000
std::vector<int> generateArrays() {
    std::srand(std::time(nullptr));
    std::vector<int> array1(4);
    std::vector<int> array2(4);
    std::vector<int> array3(8);
    std::vector<int> array4(16);
    std::vector<int> array5(32);

    // 生成数组1
    for (int i = 0; i < 4; ++i) {
        array1[i] = std::rand() % 10 + 1;
    }

    // 生成数组2
    int multiplier2;
    do {
        multiplier2 = std::rand() % 9 + 2;
    } while (*std::max_element(array1.begin(), array1.end()) * multiplier2 > 1000);
    for (int i = 0; i < 4; ++i) {
        array2[i] = array1[i] * multiplier2;
    }

    // 生成数组3
    int multiplier3;
    do {
        multiplier3 = std::rand() % 9 + 2;
    } while (std::max(*std::max_element(array1.begin(), array1.end()) * multiplier3,
        *std::max_element(array2.begin(), array2.end()) * multiplier3) > 1000);
    for (int i = 0; i < 4; ++i) {
        array3[i] = array1[i] * multiplier3;
        array3[i + 4] = array2[i] * multiplier3;
    }

    // 生成数组4
    int multiplier4;
    int max13 = std::max(*std::max_element(array1.begin(), array1.end()), *std::max_element(array3.begin(), array3.end()));
    int max23 = std::max(*std::max_element(array2.begin(), array2.end()), *std::max_element(array3.begin() + 4, array3.end()));
    do {
        multiplier4 = std::rand() % 9 + 2;
    } while (std::max(max13 * multiplier4, max23 * multiplier4) > 1000);
    for (int i = 0; i < 4; ++i) {
        array4[i] = array1[i] * multiplier4;
        array4[i + 4] = array2[i] * multiplier4;
        array4[i + 8] = array3[i] * multiplier4;
        array4[i + 12] = array3[i + 4] * multiplier4;
    }

    // 生成数组5
    int multiplier5;
    int max14 = std::max(max13, *std::max_element(array4.begin(), array4.begin() + 4));
    int max24 = std::max(max23, *std::max_element(array4.begin() + 4, array4.end()));
    do {
        multiplier5 = std::rand() % 9 + 2;
    } while (std::max(max14 * multiplier5, max24 * multiplier5) > 1000);
    for (int i = 0; i < 4; ++i) {
        array5[i] = array1[i] * multiplier5;
        array5[i + 4] = array2[i] * multiplier5;
        array5[i + 8] = array3[i] * multiplier5;
        array5[i + 12] = array3[i + 4] * multiplier5;
        array5[i + 16] = array4[i] * multiplier5;
        array5[i + 20] = array4[i + 4] * multiplier5;
        array5[i + 24] = array4[i + 8] * multiplier5;
        array5[i + 28] = array4[i + 12] * multiplier5;
    }

    // 合并五个数组
    std::vector<int> allNumbers;
    allNumbers.insert(allNumbers.end(), array1.begin(), array1.end());
    allNumbers.insert(allNumbers.end(), array2.begin(), array2.end());
    allNumbers.insert(allNumbers.end(), array3.begin(), array3.end());
    allNumbers.insert(allNumbers.end(), array4.begin(), array4.end());
    allNumbers.insert(allNumbers.end(), array5.begin(), array5.end());

    // 打乱顺序
    std::random_shuffle(allNumbers.begin(), allNumbers.end());

    return allNumbers;
}

// 初始化矩阵
std::vector<std::vector<int>> initializeMatrix() {
    std::vector<int> allNumbers = generateArrays();
    std::vector<std::vector<int>> matrix(8, std::vector<int>(8));
    int index = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            matrix[i][j] = allNumbers[index++];
        }
    }
    return matrix;
}

// 显示矩阵
void displayMatrix(const std::vector<std::vector<int>>& matrix) {
    int size = matrix.size();
    // 输出列号
    std::cout << "   ";
    for (int i = 1; i <= size; ++i) {
        std::cout << "[" << i << "]\t";
    }
    std::cout << std::endl;
    // 输出行号和矩阵
    for (int i = 0; i < size; ++i) {
        std::cout << "[" << i + 1 << "] ";
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] == 1) {
                std::cout << " \t";
            }
            else {
                std::cout << matrix[i][j] << "\t";
            }
        }
        std::cout << std::endl;
    }
}

// 验证输入是否为合法的整数
bool isValidInput(int& num) {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

// 验证坐标是否有效
bool isValidChoice(int row1, int col1, int row2, int col2, int size) {
    return row1 >= 0 && row1 < size && col1 >= 0 && col1 < size &&
        row2 >= 0 && row2 < size && col2 >= 0 && col2 < size;
}

// 消除或计算
void eliminateOrCalculate(std::vector<std::vector<int>>& matrix, int row1, int col1, int row2, int col2) {
    int num1 = matrix[row1][col1];
    int num2 = matrix[row2][col2];

    if (num1 == num2) {
        matrix[row1][col1] = 1;
        matrix[row2][col2] = 1;
    }
    else {
        int divisor = gcd(num1, num2);
        matrix[row1][col1] /= divisor;
        matrix[row2][col2] /= divisor;
    }
}

// 判断游戏是否结束
bool isGameOver(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int num : row) {
            if (num != 1) {
                return false;
            }
        }
    }
    return true;
}

// 判断是否无解
bool isNoSolution(const std::vector<std::vector<int>>& matrix) {
    int size = matrix.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] != 0) {
                for (int k = 0; k < size; ++k) {
                    for (int l = 0; l < size; ++l) {
                        if ((k != i || l != j) && matrix[k][l] != 0) {
                            int num1 = matrix[i][j];
                            int num2 = matrix[k][l];
                            if (num1 == num2 || gcd(num1, num2) > 1) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

// 倒计时函数
bool countdown(int seconds) {
    auto start = std::chrono::steady_clock::now();
    auto end = start + std::chrono::seconds(seconds);

    while (std::chrono::steady_clock::now() < end) {
        auto remaining = std::chrono::duration_cast<std::chrono::seconds>(end - std::chrono::steady_clock::now()).count();
        std::cout << "剩余时间: " << remaining << " 秒" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "时间到！游戏失败。" << std::endl;
    return false;
}

int main() {
    std::cout << "欢迎来到数字消除游戏！" << std::endl;
    std::cout << "游戏规则：选择两个数字，如果数字相同则消除，如果不同则用它们的最大公约数进行约分。" << std::endl;
    std::cout << "当所有数字都变为 1 时，游戏成功；当剩余数字无法相互找出最大公约数时，游戏失败。" << std::endl;
    std::cout << "你有 60 秒的时间完成游戏。" << std::endl;

    while (true) {
        std::vector<std::vector<int>> matrix = initializeMatrix();
        std::thread countdownThread(countdown, 60);

        while (!isGameOver(matrix)) {
            displayMatrix(matrix);
            if (isNoSolution(matrix)) {
                std::cout << "游戏失败" << std::endl;
                countdownThread.detach();
                break;
            }

            int row1, col1, row2, col2;
            std::cout << "请输入要操作的两个数字的行和列（1 - 8），用空格分隔（格式：行1 列1 行2 列2）: ";
            std::cin >> row1 >> col1 >> row2 >> col2;
            if (!isValidInput(row1) || !isValidInput(col1) || !isValidInput(row2) || !isValidInput(col2)) {
                std::cout << "输入无效，请输入合法的整数。" << std::endl;
                continue;
            }
            row1--; col1--; row2--; col2--;

            if (isValidChoice(row1, col1, row2, col2, 8)) {
                eliminateOrCalculate(matrix, row1, col1, row2, col2);
            }
            else {
                std::cout << "输入的坐标无效，请重新输入。" << std::endl;
            }
        }

        if (countdownThread.joinable()) {
            countdownThread.detach();
        }

        if (isGameOver(matrix)) {
            std::cout << "恭喜你，游戏成功结束！" << std::endl;
        }

        char choice;
        std::cout << "是否重新开始游戏？(y/n): ";
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break;
        }
    }

    return 0;
}