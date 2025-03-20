#include "Univers.hxx"

class VTKWriter {

    private:

    static void writeHeader(std::ofstream& file, Univers& univers);

    static void writeParticlesData(std::ofstream& file, Univers& univers);

    public:

    static void write(const std::string& filename, Univers& univers);
};