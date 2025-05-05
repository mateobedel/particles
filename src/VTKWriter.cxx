#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm> 

#include "VTKWriter.hxx"


void VTKWriter::writeHeader(std::ofstream& file, Univers& univers) {


    file << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"BigEndian\">\n";
    file << "  <UnstructuredGrid>\n";
    file << "    <Piece NumberOfPoints=\""<< univers.getNbParticule() <<"\" NumberOfCells=\"0\">\n";

    writeParticlesData(file, univers);

    file << "    </Piece>\n";
    file << "  </UnstructuredGrid>\n";
    file << "</VTKFile>\n";

    file.close();
}


void VTKWriter::writeParticlesData(std::ofstream& file, Univers& univers) {

    const std::vector<Cellule>& cellules = univers.getCellules();
    const std::vector<Particule>& particules = univers.getParticules();

    //Position
    file << "      <Points>\n";
    file << "        <DataArray name=\"Position\" type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">\n";
    
    for(auto& c : cellules)
        for (auto& i : c.partInd)
            file << particules[i].getPosition() << " ";
        

    file << "\n";
    file << "        </DataArray>\n";
    file << "      </Points>\n";


    //Vitesse
    file << "      <PointData Vectors=\"vector\">\n";
    file << "        <DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">\n";
    
    for(size_t i = 0; i < particules.size(); i++) {
        file << particules[i].getVitesse();
        if (i != particules.size()-1) file << " "; 
    }
    file << "\n";
    file << "        </DataArray>\n";

    //Masse
    file << "        <DataArray type=\"Float32\" Name=\"Masse\" format=\"ascii\">\n";

    for(size_t i = 0; i < particules.size(); i++) {
        file << particules[i].getMasse();
        if (i != particules.size()-1) file << " ";
    }
    file << "\n";
    file << "        </DataArray>\n";
    file << "      </PointData>\n";


    //Structure
    file << "      <Cells>\n";
    file << "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n";
    file << "        </DataArray>\n";
    file << "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n";
    file << "        </DataArray>\n";
    file << "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n";
    file << "        </DataArray>\n";
    file << "      </Cells>\n";
}


void VTKWriter::write(const std::string& filename, Univers& univers) {

    std::ofstream file(filename);
    
    if (!file) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
        return;
    }

    writeHeader(file, univers);
}

int VTKWriter::readVTKNumber(int argc, char* argv[]) {

    int nb_vtk = 0;  

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        const std::string prefix = "-nb_vtk=";
        if (arg.find(prefix) == 0) {
            int val = std::atoi(arg.substr(prefix.size()).c_str());
            if (val < 0) std::cerr << "Erreur : -nb_vtk doit être >= 0" << std::endl;
            else nb_vtk = val;
            
        }
    }
    return nb_vtk;
}
    


std::vector<int> VTKWriter::genOutputSteps(int vtkNumber, int steps) {
    std::vector<int> outSteps;

    if (vtkNumber == 1) {
        outSteps.push_back(0);
    } else {
        outSteps.reserve(vtkNumber);
        for (int k = 0; k < vtkNumber; ++k) {
            outSteps.push_back(k * (steps - 1) / (vtkNumber - 1));
        }
    }
    return outSteps;
}


void VTKWriter::writeOnOutSteps(int step, float t, const std::vector<int>& outSteps, Univers& u) {
    
    static int nextOut = 0;

    if (nextOut < (int)outSteps.size() && step == outSteps[nextOut]) {
        std::ostringstream time;
        time << nextOut;
        write("sim_" + time.str() + ".vtu", u);
        nextOut++;
    }
}