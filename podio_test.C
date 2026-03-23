R__LOAD_LIBRARY(libpodio.so)
R__LOAD_LIBRARY(libpodioRootIO.so)
R__LOAD_LIBRARY(libedm4hep.so)
R__LOAD_LIBRARY(libedm4hepDict.so)
R__LOAD_LIBRARY(libedm4hepUtils.so)
R__LOAD_LIBRARY(libedm4hepRDF.so)
R__LOAD_LIBRARY(libedm4eic.so)
R__LOAD_LIBRARY(libedm4eicDict.so)

#include "podio/Frame.h"
#include "podio/ROOTReader.h"

void podio_test()
{
    
    podio::ROOTReader* reader = new podio::ROOTReader();
    reader->openFile("root://dtn-eic.jlab.org:1094//volatile/eic/EPIC//RECO/26.02.0/epic_craterlake/DIS/NC/18x275/minQ2=10/pythia8NCDIS_18x275_minQ2=10_beamEffects_xAngle=-0.025_hiDiv_1.0000.eicrecon.edm4eic.root");

    for( size_t ev = 0; ev < reader->getEntries("events"); ev++ )
    {   
        auto raw = reader->readEntry("events", ev);  // Use readEntry with index instead
        podio::Frame event(std::move(raw));

        edm4hep::MCParticleCollection meMC;
	    meMC.setSubsetCollection();
	
        const auto& mcparts = event.get<edm4hep::MCParticleCollection>("MCParticles");
        for (const auto& mcp : mcparts) 
        {
            if ( mcp.getPDG() == 11 && mcp.getGeneratorStatus() == 1 ) 
                meMC.push_back(mcp);
        }
    }

    return;
}
