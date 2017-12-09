#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QDataStream>

class Settings
{
    int _matrix_size;
    int _seed;
    bool _dark_theme;
public:
    enum {
        SEED_IS_NOT_SET = INT32_MAX
    };

    Settings(): _matrix_size(4), _seed(SEED_IS_NOT_SET), _dark_theme(false) {}
    Settings(int matrixSize, int seed, bool darkTheme): _matrix_size(matrixSize), _seed(seed), _dark_theme(darkTheme) { }

    void setMatrixSize(int matrixSize);
    void setSeed(int seed);
    void setDarkTheme(bool enabled) { _dark_theme = enabled; }

    int matrixSize() const { return _matrix_size; }
    int seed() const { return _seed; }
    bool darkTheme() const { return _dark_theme; }

    QString resourceFolder() const { return _dark_theme ? QString(":/images/resources/Dark/") : QString(":/images/resources/Light/"); }
};

QDataStream &operator<<(QDataStream &out, const Settings &settings);
QDataStream &operator>>(QDataStream &in, Settings &settings);

#endif // SETTINGS_H
