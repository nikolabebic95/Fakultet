/**
 * \brief Loads the overlay from file to the address
 * \param filename Name of the file
 * \param address Address of overlay
 */
void sys_loadBinary(const char* filename, void* address);

/**
 * \brief Struct representing the overlay descriptor
 */
struct OverlayDescr{
    const char* filename; /**< File where overlay is */
    void* addr; /**< Address in memory where overlay is */
    bool isLoaded; /**< Whether the overlay is loaded */
};

const int numOfOverlays=100; /**< Number of overlays */
OverlayDescr overlays[numOfOverlays]; /**< Array of descriptors */

const int numOfProcs=50; /**< Number of procedures */
OverlayDescr* procedureMap[numOfProcs]; /**< Array of procedures */

/**
 * \brief Ensures overlay is loaded
 * \param proc_id Index of the procedure
 */
void ensureOverlay(int proc_id){
    OverlayDescr* overlay=procedureMap[proc_id];
    if(!overlay->isLoaded){
        sys_loadBinary(overlay->filename, overlay->adress);

        for(int i=0; i<numOfOverlays; i++)
            if(overlay->addr==overlays[i].addr)
                overlays[i].isLoaded=false;

        overlay->isLoaded=true;
    }
}