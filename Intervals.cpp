#include <iostream>

void interval_calculator();

int main();

void interval_calculator() {
    bool run{true}, initialized{false}, unknown{false}, saved{false};
    double a{}, b{}, temp_a{}, temp_b{}, memory_a{}, memory_b{};
    std::string input{};
    while (run) {
        std::cout << "input :> ";
        std::cin >> input;
        if (input == "exit") {
            run = false;
        } else if (input == "enter") {
            std::cin >> temp_a >> temp_b;

            if (temp_a > temp_b) {
                std::cout << "Error: invalid interval as " << temp_a << " > " << temp_b << std::endl;
            } else {
                initialized = true;
                a = temp_a;
                b = temp_b;
            }
        } else if (input == "negate") {
            temp_a = -a;
            a = -b;
            b = temp_a;
        } else if (input == "invert") {
            if (a <= 0 && b >= 0 && initialized) {
                std::cout << "Error: division by zero" << std::endl;
                initialized = false;
                a = 0;
                b = 0;
            } else {
                temp_a = 1 / a;
                a = 1 / b;
                b = temp_a;
            }
        } else if (input == "ms") {
            memory_a = a;
            memory_b = b;
            if (initialized) {
                saved = true;
            }
        } else if (input == "mr") {
            if (saved) {
                a = memory_a;
                b = memory_b;
            }
        } else if (input == "mc") {
            saved = false;
            memory_a = 0;
            memory_b = 0;
        } else if (input == "m+") {
            if (saved && initialized) {
                memory_a += a;
                memory_b += b;
            }
        } else if (input == "m-") {
            if (saved && initialized) {
                memory_a -= a;
                memory_b -= b;
            }
        } else if (input == "scalar_add") {
            std::cin >> temp_a;
            if (initialized) {
                a += temp_a;
                b += temp_a;
            }
        } else if (input == "scalar_subtract") {
            std::cin >> temp_a;
            if (initialized) {
                a -= temp_a;
                b -= temp_a;
            }
        } else if (input == "scalar_multiply") {
            std::cin >> temp_a;
            if (initialized && temp_a >= 0) {
                a *= temp_a;
                b *= temp_a;
            } else if (initialized && temp_a <= 0) {
                temp_b = a;
                a = b * temp_a;
                b = temp_b * temp_a;
            }
        } else if (input == "scalar_divide") {
            std::cin >> temp_a;
            if (initialized && temp_a > 0) {
                a /= temp_a;
                b /= temp_a;
            } else if (initialized && temp_a < 0) {
                temp_b = a;
                a = b / temp_a;
                b = temp_b / temp_a;
            } else if (initialized && temp_a == 0) {
                std::cout << "Error: division by zero" << std::endl;
                initialized = false;
                a = 0;
                b = 0;
            }
        } else if (input == "scalar_divided_by") {
            std::cin >> temp_a;
            if (initialized && a <= 0 && b >= 0) {
                std::cout << "Error: division by zero" << std::endl;
                a = 0;
                b = 0;
                initialized = false;
            } else if (initialized && temp_a <= 0) {
                a = temp_a / a;
                b = temp_a / b;
            } else if (initialized) {
                temp_b = temp_a / a;
                a = temp_a / b;
                b = temp_b;
            }
        } else if (input == "interval_add") {
            std::cin >> temp_a >> temp_b;
            if (temp_a > temp_b) {
                std::cout << "Error: invalid interval as " << temp_a << " > " << temp_b << std::endl;
            } else if (initialized) {
                a += temp_a;
                b += temp_b;
            }
        } else if (input == "interval_subtract") {
            std::cin >> temp_a >> temp_b;
            if (temp_a > temp_b) {
                std::cout << "Error: invalid interval as " << temp_a << " > " << temp_b << std::endl;
            } else if (initialized) {
                a -= temp_b;
                b -= temp_a;
            }
        } else if (input == "interval_multiply") {
            std::cin >> temp_a >> temp_b;
            if (temp_a > temp_b) {
                std::cout << "Error: invalid interval as " << temp_a << " > " << temp_b << std::endl;
            } else {
                double ac{a * temp_a}, ad{a * temp_b}, bc{b * temp_a}, bd{b * temp_b};
                a = std::min(ac, ad);
                a = std::min(a, bc);
                a = std::min(a, bd);
                b = std::max(ac, ad);
                b = std::max(b, bc);
                b = std::max(b, bd);
            }
        } else if (input == "interval_divide") {
            std::cin >> temp_a >> temp_b;
            if (temp_a > temp_b) {
                std::cout << "Error: invalid interval as " << temp_a << " > " << temp_b << std::endl;
            } else if (temp_a <= 0 && temp_b >= 0) {
                std::cout << "Error: division by zero" << std::endl;
                a = 0;
                b = 0;
                initialized = false;
            } else {
                double ac{a / temp_a}, ad{a / temp_b}, bc{b / temp_a}, bd{b / temp_b};
                a = std::min(ac, ad);
                a = std::min(a, bc);
                a = std::min(a, bd);
                b = std::max(ac, ad);
                b = std::max(b, bc);
                b = std::max(b, bd);
            }
        } else if (input == "intersect") {
            std::cin >> temp_a >> temp_b;
            if (temp_a > temp_b) {
                std::cout << "Error: invalid interval as " << temp_a << " > " << temp_b << std::endl;
            } else if (initialized) {
                if (b < temp_a || a > temp_b) {
                    initialized = false;
                    a = 0;
                    b = 0;
                } else if (a <= temp_a && b >= temp_b) {
                    a = temp_a;
                    b = temp_b;
                } else if (a <= temp_a && temp_b >= b) {
                    a = temp_a;
                } else if (a >= temp_a && b >= temp_b) {
                    b = temp_b;
                }
            }
        } else if (input == "integers") {
            if (initialized) {
                for (int i = a; i <= b; ++i) {
                    std::cout << i;
                    if (i <= b - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
            }
        } else if (input == "cartesian_integers") {
            std::cin >> temp_a >> temp_b;
            if (temp_a > temp_b) {
                std::cout << "Error: invalid interval as " << temp_a << " > " << temp_b << std::endl;
            } else if (initialized && a >= 0) {
                for (int i = (a + 0.9999); i <= b; ++i) {
                    for (int j = temp_a; j <= temp_b; ++j) {
                        std::cout << "(" << i << "," << j << ")";
                        if (i <= b - 1 || j <= temp_b - 0.99) {
                            std::cout << ", ";
                        }
                    }
                }
                std::cout << std::endl;
            } else {
                for (int i = a; i <= b; ++i) {
                    for (int j = temp_a; j <= temp_b; ++j) {
                        std::cout << "(" << i << "," << j << ")";
                        if (i <= b - 1 || j <= temp_b - 0.99) {
                            std::cout << ", ";
                        }
                    }
                }
                std::cout << std::endl;
            }
        } else {
            unknown = true;
            std::cout << "Error: illegal command" << std::endl;
        }
        if (initialized && run && !unknown) {
            std::cout << "[" << a << ", " << b << "]" << std::endl;
        } else if (run && !unknown) {
            std::cout << "--" << std::endl;
        }
        unknown = false;
    }
    std::cout << "Bye bye: Terminating interval calculator program.";
}

int main() {
    interval_calculator();
    return 0;
}