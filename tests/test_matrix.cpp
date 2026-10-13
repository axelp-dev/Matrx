#include "TestRunner.h"
#include "core/Matrix.h"
#include <iomanip>
#include <stdexcept>

void run_matrix_tests() {
    std::cout << Test::CYAN << "[SUITE] " << Test::RESET << "Matrix Core Operations\n";

    // Test 1 : Constructeurs, initialisation et dimensions
    {
        std::cout << "  - Dimensions & initialization      " << std::setw(15) << std::setfill('.') << "";
        int fails = Test::failed_count;

        Matrix m_fill(2, 3, 4.5);
        ASSERT_TRUE(m_fill.get_rows() == 2);
        ASSERT_TRUE(m_fill.get_cols() == 3);
        ASSERT_FLOAT_EQ(m_fill(0, 0), 4.5f);
        ASSERT_FLOAT_EQ(m_fill(1, 2), 4.5f);

        // Constructeur par copie (deep-copy)
        Matrix m_copy(m_fill);
        ASSERT_TRUE(m_copy.get_rows() == 2);
        ASSERT_TRUE(m_copy.get_cols() == 3);
        ASSERT_FLOAT_EQ(m_copy(0, 0), 4.5f);

        // Vérification de l'indépendance mémoire
        m_copy(0, 0) = 10.0;
        ASSERT_FLOAT_EQ(m_copy(0, 0), 10.0f);
        ASSERT_FLOAT_EQ(m_fill(0, 0), 4.5f);

        if (Test::failed_count == fails) {
            std::cout << " " << Test::GREEN << "[OK]" << Test::RESET << "\n";
        } else {
            std::cout << " " << Test::RED << "[FAIL]" << Test::RESET << "\n";
        }
    }

    // Test 2 : Opérateur d'addition (+)
    {
        std::cout << "  - Matrix addition operator (+)     " << std::setw(15) << std::setfill('.') << "";
        int fails = Test::failed_count;

        Matrix a(2, 2, 2.0);
        Matrix b(2, 2, 3.5);

        Matrix* res = a + b;
        ASSERT_TRUE(res != nullptr);
        ASSERT_FLOAT_EQ((*res)(0, 0), 5.5f);
        ASSERT_FLOAT_EQ((*res)(1, 1), 5.5f);
        delete res;

        // Test de détection d'incompatibilité de dimensions
        Matrix incompatible(3, 2, 1.0);
        bool exception_caught = false;
        try {
            Matrix* bad = a + incompatible;
            delete bad;
        } catch (const std::invalid_argument&) {
            exception_caught = true;
        }
        ASSERT_TRUE(exception_caught);

        if (Test::failed_count == fails) {
            std::cout << " " << Test::GREEN << "[OK]" << Test::RESET << "\n";
        } else {
            std::cout << " " << Test::RED << "[FAIL]" << Test::RESET << "\n";
        }
    }

    // Test 3 : Produit de Hadamard
    {
        std::cout << "  - Hadamard element-wise product    " << std::setw(15) << std::setfill('.') << "";
        int fails = Test::failed_count;

        Matrix a(2, 2, 3.0);
        Matrix b(2, 2, 4.0);

        Matrix* res = a.hadamard(b);
        ASSERT_TRUE(res != nullptr);
        ASSERT_FLOAT_EQ((*res)(0, 0), 12.0f);
        ASSERT_FLOAT_EQ((*res)(1, 1), 12.0f);
        delete res;

        // Exception sur dimensions incompatibles
        Matrix incompatible(2, 4, 1.0);
        bool exception_caught = false;
        try {
            Matrix* bad = a.hadamard(incompatible);
            delete bad;
        } catch (const std::invalid_argument&) {
            exception_caught = true;
        }
        ASSERT_TRUE(exception_caught);

        if (Test::failed_count == fails) {
            std::cout << " " << Test::GREEN << "[OK]" << Test::RESET << "\n";
        } else {
            std::cout << " " << Test::RED << "[FAIL]" << Test::RESET << "\n";
        }
    }

    // Test 4 : Opérateur de comparaison (!=)
    {
        std::cout << "  - Matrix inequality operator (!=)  " << std::setw(15) << std::setfill('.') << "";
        int fails = Test::failed_count;

        Matrix a(2, 2, 1.0);
        Matrix b(2, 2, 1.0);
        Matrix diff_dim(3, 3, 1.0);

        // a et b sont identiques
        ASSERT_TRUE((a != b) == false);

        // Modification d'un seul élément
        b(1, 1) = 2.0;
        ASSERT_TRUE((a != b) == true);

        // Dimensions différentes
        ASSERT_TRUE((a != diff_dim) == true);

        if (Test::failed_count == fails) {
            std::cout << " " << Test::GREEN << "[OK]" << Test::RESET << "\n";
        } else {
            std::cout << " " << Test::RED << "[FAIL]" << Test::RESET << "\n";
        }
    }
}