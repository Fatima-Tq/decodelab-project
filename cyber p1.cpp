#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <unordered_set>

class PasswordStrengthChecker {
private:
    // Character pools for entropy calculation
    const std::string lowercase_pool = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercase_pool = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digit_pool = "0123456789";
    const std::string special_pool = "!@#$%^&*()_+-=[]{}|;:,.<>?/~";

    // Common passwords for pattern checking
    const std::unordered_set<std::string> common_passwords = {
        "password", "123456", "12345678", "1234", "qwerty",
        "abc123", "monkey", "letmein", "dragon", "111111",
        "admin", "password123", "welcome", "login", "master",
        "sunshine", "iloveyou", "princess", "rockyou", "trustno1"
    };

    // Strength rating thresholds (in bits of entropy)
    struct Thresholds {
        static constexpr double VERY_WEAK = 0.0;
        static constexpr double WEAK = 30.0;
        static constexpr double MEDIUM = 50.0;
        static constexpr double STRONG = 70.0;
        static constexpr double VERY_STRONG = 100.0;
    };

    // Report structure to hold analysis results
    struct Report {
        std::string password_entered;
        size_t length;
        std::string criteria_met;
        bool has_lowercase;
        bool has_uppercase;
        bool has_digits;
        bool has_special;
        double entropy_bits;
        std::string strength_rating;
        bool is_common_pattern;
        std::vector<std::string> recommendations;
    };


    void validateInput(const std::string& password) {
        if (password.empty()) {
            throw std::invalid_argument("Invalid input: Password cannot be empty.");
        }

        // Check if string contains only whitespace
        bool onlyWhitespace = true;
        for (char c : password) {
            if (!std::isspace(static_cast<unsigned char>(c))) {
                onlyWhitespace = false;
                break;
            }
        }

        if (onlyWhitespace) {
            throw std::invalid_argument("Invalid input: Password cannot be only whitespace.");
        }
    }


    double calculateEntropy(const std::string& password) {
        size_t pool_size = 0;

        // Determine the character pool used
        for (char c : password) {
            if (std::islower(static_cast<unsigned char>(c))) {
                pool_size = std::max(pool_size, lowercase_pool.length());
                break;
            }
        }

        for (char c : password) {
            if (std::isupper(static_cast<unsigned char>(c))) {
                pool_size = std::max(pool_size, uppercase_pool.length());
                break;
            }
        }

        for (char c : password) {
            if (std::isdigit(static_cast<unsigned char>(c))) {
                pool_size = std::max(pool_size, digit_pool.length());
                break;
            }
        }

        for (char c : password) {
            if (special_pool.find(c) != std::string::npos) {
                pool_size = std::max(pool_size, special_pool.length());
                break;
            }
        }

        // If only spaces or special cases (should not happen after validation)
        if (pool_size == 0) {
            return 0.0;
        }

        // Entropy = length * log2(pool_size)
        double entropy = password.length() * std::log2(static_cast<double>(pool_size));
        return entropy;
    }

 
    bool checkForCommonPatterns(const std::string& password) {
        std::string lower_password = password;
        std::transform(lower_password.begin(), lower_password.end(),
            lower_password.begin(), ::tolower);
        return common_passwords.find(lower_password) != common_passwords.end();
    }

    std::string determineStrength(double entropy, bool is_common) {
        if (is_common || entropy < Thresholds::WEAK) {
            return "Very Weak";
        }
        else if (entropy < Thresholds::MEDIUM) {
            return "Weak";
        }
        else if (entropy < Thresholds::STRONG) {
            return "Medium";
        }
        else if (entropy < Thresholds::VERY_STRONG) {
            return "Strong";
        }
        else {
            return "Very Strong";
        }
    }

  
    std::vector<std::string> generateRecommendations(
        const std::string& password,
        bool has_lower,
        bool has_upper,
        bool has_digit,
        bool has_special,
        bool is_common
    ) {
        std::vector<std::string> recommendations;
        size_t length = password.length();

        if (length < 8) {
            recommendations.push_back("Increase length to at least 12 characters.");
        }
        if (!has_upper) {
            recommendations.push_back("Include at least one uppercase letter.");
        }
        if (!has_lower) {
            recommendations.push_back("Include at least one lowercase letter.");
        }
        if (!has_digit) {
            recommendations.push_back("Include at least one number.");
        }
        if (!has_special) {
            recommendations.push_back("Include at least one special character (!@#$%^&* etc.).");
        }
        if (is_common) {
            recommendations.push_back("Avoid using common or easily guessable passwords.");
        }

        if (recommendations.empty()) {
            recommendations.push_back("Password meets all recommended criteria.");
        }

        return recommendations;
    }

public:
   
    Report analyze(const std::string& password) {
        // Validation
        validateInput(password);

        //Initial Checks
        size_t length = password.length();
        bool has_lower = false;
        bool has_upper = false;
        bool has_digit = false;
        bool has_special = false;

        for (char c : password) {
            if (std::islower(static_cast<unsigned char>(c))) has_lower = true;
            if (std::isupper(static_cast<unsigned char>(c))) has_upper = true;
            if (std::isdigit(static_cast<unsigned char>(c))) has_digit = true;
            if (special_pool.find(c) != std::string::npos) has_special = true;
        }

        //Count criteria met
        int criteria_met = (has_lower ? 1 : 0) + (has_upper ? 1 : 0) +
            (has_digit ? 1 : 0) + (has_special ? 1 : 0);

        //Entropy Calculation
        double entropy = calculateEntropy(password);

        //Check for common patterns
        bool is_common = checkForCommonPatterns(password);

        //Determine Strength Rating
        std::string strength = determineStrength(entropy, is_common);

        //Generate Recommendations
        std::vector<std::string> recommendations = generateRecommendations(
            password, has_lower, has_upper, has_digit, has_special, is_common
        );

        //Prepare Report
        Report report;
        report.password_entered = "********";  
        report.length = length;
        report.criteria_met = std::to_string(criteria_met) + "/4";
        report.has_lowercase = has_lower;
        report.has_uppercase = has_upper;
        report.has_digits = has_digit;
        report.has_special = has_special;
        report.entropy_bits = std::round(entropy * 100.0) / 100.0;
        report.strength_rating = strength;
        report.is_common_pattern = is_common;
        report.recommendations = recommendations;

        return report;
    }

   
    void displayReport(const Report& report) {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << "  PASSWORD STRENGTH ANALYSIS REPORT" << std::endl;
   
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "  Strength Rating:        " << report.strength_rating << std::endl;
        std::cout << "  Entropy (bits):         " << std::fixed << std::setprecision(2)
            << report.entropy_bits << std::endl;
        std::cout << "  Length:                 " << report.length << std::endl;
        std::cout << "  Criteria Met:           " << report.criteria_met << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        std::cout << "  CHARACTER DIVERSITY:" << std::endl;
        std::cout << "    - Lowercase:           "
            << (report.has_lowercase ? "correct" : "no") << std::endl;
        std::cout << "    - Uppercase:           "
            << (report.has_uppercase ? "correct" : "no") << std::endl;
        std::cout << "    - Digits:              "
            << (report.has_digits ? "✓" : "✗") << std::endl;
        std::cout << "    - Special Characters:  "
            << (report.has_special ? "✓" : "✗") << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        std::cout << "  RECOMMENDATIONS:" << std::endl;
        for (const auto& rec : report.recommendations) {
            std::cout << "    - " << rec << std::endl;
        }
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "  Note: Your actual password was not stored or logged." << std::endl;
        std::cout << std::string(60, '=') << "\n" << std::endl;
    }
};

int main() {
    PasswordStrengthChecker checker;

    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "   PASSWORD STRENGTH CHECKER" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    while (true)
    {
        std::cout << "\n[1] Check Password Strength" << std::endl;
        std::cout << "[2] Exit" << std::endl;
        std::cout << "Select an option: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            try {
                std::cout << "Enter a password to analyze: ";
                std::string password;
                std::getline(std::cin, password);

                auto report = checker.analyze(password);
                checker.displayReport(report);
            }
            catch (const std::invalid_argument& e) {
                std::cout << "[ERROR] " << e.what() << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << "[ERROR] An unexpected error occurred: " << e.what() << std::endl;
            }
        }
        else if (choice == "2") {
            std::cout << "\nExiting Password Strength Checker. Stay secure!" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid choice. Please select 1 or 2." << std::endl;
        }
    }

    return 0;
}