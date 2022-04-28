// STEP Read Methods
#include <STEPControl_Reader.hxx>
#include <TopoDS_Shape.hxx>
// STL Read & Write Methods
#include <StlAPI_Writer.hxx>
#include <BRepMesh_IncrementalMesh.hxx>

#include <iostream>

bool step2stl(char *in, char *out, bool ascii_mode = false)
{
    // Read from STEP
    STEPControl_Reader reader;
    IFSelect_ReturnStatus stat = reader.ReadFile(in);

    Standard_Integer NbRoots = reader.NbRootsForTransfer();
    Standard_Integer NbTrans = reader.TransferRoots();
    TopoDS_Shape Original_Solid = reader.OneShape();
    // Write to STL
    try
    {
        StlAPI_Writer stlWriter = StlAPI_Writer();
        stlWriter.ASCIIMode() = ascii_mode;
        BRepMesh_IncrementalMesh Mesh(Original_Solid, 0.01);
        stlWriter.Write(Original_Solid, out);
        std::cout << "Success, out file: " << out << std::endl;
        return true;
    }
    catch (Standard_Failure &e)
    {
        std::cerr << e.GetMessageString() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Failed to convert!" << std::endl;
    }
    std::cout << "Failed\n";
    return false;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " file.step file.stl [using_ascii_mode]" << std::endl;
        return 1;
    }
    bool ascii_mode = false;
    if (argc >= 4)
    {
        ascii_mode = !!atoi(argv[3]);
    }

    return step2stl(argv[1], argv[2], ascii_mode);
}