#include "settings.h"

const int MINIMUM_MATRIX_SIZE = 2;
const int MAXIMUM_MATRIX_SIZE = 12;
const int MINIMUM_SEED = 0;
const int MAXIMUM_SEED = INT32_MAX - 1;

void Settings::setMatrixSize(int matrixSize)
{
    if (matrixSize >= MINIMUM_MATRIX_SIZE && matrixSize <= MAXIMUM_MATRIX_SIZE)
    {
        _matrix_size = matrixSize;
    }
}

void Settings::setSeed(int seed)
{
    if (seed >= MINIMUM_SEED && seed <= MAXIMUM_SEED)
    {
        _seed = seed;
    }
}

QDataStream& operator<<(QDataStream &out, const Settings &settings)
{
    out << settings.matrixSize() << settings.seed() << settings.darkTheme();
    return out;
}

QDataStream &operator>>(QDataStream &in, Settings &settings)
{
    int matrixSize, seed;
    bool darkTheme;
    in >> matrixSize >> seed >> darkTheme;
    settings = Settings(matrixSize, seed, darkTheme);
    return in;
}
