#include <iostream>
#include <fstream>
#include <vector>

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

    std::vector<Particule> particules = univers.getParticules();

    //Position
    file << "      <Points>\n";
    file << "        <DataArray name=\"Position\" type=\"Float32\" NumberOfComponents=\"" << univers.getDimension() << "\" format=\"ascii\">\n";
    

    for(size_t i = 0; i < particules.size(); i++) {
        if (univers.getDimension() == 3) file << particules[i].getPosition();
        if (univers.getDimension() == 2) file << particules[i].getPosition().x << " " << particules[i].getPosition().y;
        if (univers.getDimension() == 1) file << particules[i].getPosition().x;
        if (i != particules.size()-1) file << " ";
    }


    file << "\n";
    file << "        </DataArray>\n";
    file << "      </Points>\n";


    //Vitesse
    file << "      <PointData Vectors=\"vector\">\n";
    file << "        <DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"" << univers.getDimension() << "\" format=\"ascii\">\n";
    
    for(size_t i = 0; i < particules.size(); i++) {
        if (univers.getDimension() == 3) file << particules[i].getVitesse();
        if (univers.getDimension() == 2) file << particules[i].getVitesse().x << " " << particules[i].getVitesse().y;
        if (univers.getDimension() == 1) file << particules[i].getVitesse().x;
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