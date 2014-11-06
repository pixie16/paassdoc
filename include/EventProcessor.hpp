/** \file EventProcessor.hpp
 * \brief Generic event processor
 */
#ifndef __EVENTPROCESSOR_HPP_
#define __EVENTPROCESSOR_HPP_

#include <map>
#include <set>
#include <string>

#include <sys/times.h>

#include "Plots.hpp"
#include "TreeCorrelator.hpp"

// forward declarations
class DetectorSummary;
class RawEvent;

#ifdef useroot
class TTree;
#endif

class EventProcessor {
public:
    /** Default Constructor */
    EventProcessor();

    /** Constructor taking histogram information
     * \param [in] offset : the offset for the histograms
     * \param [in] range : the range of the histograms
     * \param [in] name : the name of the processor */
    EventProcessor(int offset, int range, std::string name);

    /** Default Destructor */
    virtual ~EventProcessor();

    /** Declares the plots for the class */
    virtual void DeclarePlots(void) {};

    /** Sets the associated types for the derived classes
    * \return The types associated with a Processor */
    virtual const std::set<std::string>& GetTypes(void) const {
        return associatedTypes;
    }

    /** \return The status of the Processor */
    virtual bool DidProcess(void) const {
        return didProcess;
    }

    /** See if the detectors of interest have any events
     * \return True if there was an event */
    virtual bool HasEvent(void) const;

    /** Initialize the processor if the detectors that require it are used in
     * the analysis
     * \param [in] event : the event to initialize with
     * \return True on success */
    virtual bool Init(RawEvent& event);

    /** Process an event. In PreProcess correlator should filled (for all
    * derived classes) and basic analysis is done. More sophisticated analysis
    * (which might also depend on other processors) should be done in Process()
    * function. PreProcess will be first called for all Processors and only
    * afterwards the Process function will be called.
    * \param[in] event : The Event to be processed
    * \return true if successfully completed */
    virtual bool PreProcess(RawEvent &event);

    /** Process an event. PreProcess function should fill correlation tree and
    * all processors should have basic parameters calculated during
    * PreProccessing. This also starts the processing timer.
    * \param[in] event : The Event to be processed
    * \return True if success */
    virtual bool Process(RawEvent &event);

    /** Wrap up the processing and update the time spent by this processor */
    void EndProcess(void);

    /** Get the name of the processor
    * \return Name of the processor */
    std::string GetName(void) const {
        return name;
    }
#ifdef useroot
    /** This functions adds the branch to the tree that will be responsible
    * for holding the data generated by this event processor
    * \param [in] tree : The tree to add the branch to
    */
    virtual bool AddBranch(TTree *tree) {return(false);};

    /** This function is called to fill the appropriate root branch. Note that
    * since ROOT branches can't be empty that the data needs to be properly
    * zeroed for events where no detectors of interest to this processor
    * triggered. This currently does nothing, add code in this function for
    * analysis to put in ROOT tree only.
    */
    virtual void FillBranch(void) {};
#endif

protected:
    std::string name; //!< Name of the Processor
    std::set<std::string> associatedTypes; //!< Set of associated types for Processor
    bool initDone;//!< True if the initialization has finished
    bool didProcess;//!< True if the process finished
    std::map<std::string, const DetectorSummary *> sumMap; //!< Map of associated detector summary

    /** Plots class for given Processor, takes care of declaration
    * and plotting within boundaries allowed by PlotsRegistry */
    Plots histo;

    /*! \brief Implementation of the plot command to interface with the DAMM
    * routines
    *
    * This is also done in the Trace class, redundant?
    * \param [in] dammId : The histogram number to plot into
    * \param [in] val1 : The x value to plot
    * \param [in] val2 : The y value to plot (if 2D histogram)
    * \param [in] val3 : The z value to plot (if 2D histogram)
    * \param [in] name : The name of the histogram
    */
    virtual void plot(int dammId, double val1, double val2 = -1,
                      double val3 = -1, const char* name="h") {
        histo.Plot(dammId, val1, val2, val3, name);
    }

    /*! \brief Declares a 1D histogram calls the C++ wrapper for DAMM
    * \param [in] dammId : The histogram number to define
    * \param [in] xSize : The range of the x-axis
    * \param [in] title : The title for the histogram
    */
    virtual void DeclareHistogram1D(int dammId, int xSize, const char* title) {
        histo.DeclareHistogram1D(dammId, xSize, title);
    }

    /*! \brief Declares a 2D histogram calls the C++ wrapper for DAMM
    * \param [in] dammId : The histogram number to define
    * \param [in] xSize : The range of the x-axis
    * \param [in] ySize : The range of the y-axis
    * \param [in] title : The title of the histogram
    */
    virtual void DeclareHistogram2D(int dammId, int xSize, int ySize,
                                    const char* title) {
        histo.DeclareHistogram2D(dammId, xSize, ySize, title);
    }

private:
    tms tmsBegin; //!< The beginning processor time
    double userTime;//!< The user time spent in the processor
    double systemTime;//!< The system time spent in the processor
    double clocksPerSecond;//!< The number of clock cycles per second
};
#endif // __EVENTPROCESSOR_HPP_
