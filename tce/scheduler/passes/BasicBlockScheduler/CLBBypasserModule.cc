/*
    Copyright (c) 2002-2009 Tampere University of Technology.

    This file is part of TTA-Based Codesign Environment (TCE).

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
 */
/**
 *
 * @file CLBBypasserModule.cc
 * 
 * Implementation of CLBBypasserModule class
 *
 * Helper scheduler module for CycleLookBackSoftwareBypasser class.
 * Creates a CycleLookBackSoftwareBypasser which is the actual bypasser class.
 *
 * @author Heikki Kultala 2007 (heikki.kultala-no.spam-tut.fi)
 * @note rating: red
 */
#include <cstdlib>

#include "ObjectState.hh"

#include "CLBBypasserModule.hh"
#include "Conversion.hh"
#include "CycleLookBackSoftwareBypasser.hh"
#include "MachineAnalysis.hh"
#include "SchedulerCmdLineOptions.hh"

// TODO: should also select values between them on machines with properties
// somewhere between these.
// default value when nothing given as parameter or environment variable.
#define BYPASS_DISTANCE 4
#define BUS_LIMITED_BYPASS_DISTANCE 9
#define RF_LIMITED_BYPASS_DISTANCE 8
#define FU_LIMITED_BYPASS_DISTANCE 3
#define NO_DRE_BYPASS_DISTANCE 2
#define BUS_LIMITED_NO_DRE_BYPASS_DISTANCE 2
#define RF_LIMITED_NO_DRE_BYPASS_DISTANCE 3
#define FU_LIMITED_NO_DRE_BYPASS_DISTANCE 2


CLBBypasserModule::CLBBypasserModule() : 
    bypassDistance_(-1), noDreBypassDistance_(-1), killDeadResults_(true), 
    bypassFromRegs_(false), bypassToRegs_(false), clbs_(NULL) {
}

CLBBypasserModule::~CLBBypasserModule() {
    if (clbs_) {
        delete clbs_; clbs_ = NULL;
    }
}

/**
 * Sets options for the plugin.
 *
 * Currently this only recognizes the bypas lookup distance option.
 *
 * @param options all options given to the schdeduler pass.
 */ 
void CLBBypasserModule::setOptions(
    const std::vector<ObjectState*>& options) {

    for (std::vector<ObjectState*>::const_iterator iter = 
             options.begin(); iter != options.end(); iter++) {
        if ((*iter)->hasAttribute("name") && 
            (*iter)->stringAttribute("name") == LOOKBACK_DISTANCE_OPTION) {
            bypassDistance_ = (*iter)->intValue();
        }
        if ((*iter)->hasAttribute("name") && 
            (*iter)->stringAttribute("name") == 
            NO_DRE_LOOKBACK_DISTANCE_OPTION) {
            noDreBypassDistance_ = (*iter)->intValue();
        }

        if ((*iter)->hasAttribute("name") && 
            (*iter)->stringAttribute("name") == KILL_DEAD_RESULTS_OPTION) {
            if ( (*iter)->stringValue() == "true" ) {
                killDeadResults_ = true;
                continue;
            }
            if ( (*iter)->stringValue() == "false" ) {
                killDeadResults_ = false;
                continue;
            }
            throw IllegalParameters(
                __FILE__,__LINE__,__func__, 
                "only true or false value allowed for " +
                KILL_DEAD_RESULTS_OPTION);
        }

        if ((*iter)->hasAttribute("name") && 
            (*iter)->stringAttribute("name") == BYPASS_FROM_REGS_OPTION) {
            if ( (*iter)->stringValue() == "true" ) {
                bypassFromRegs_ = true;
                continue;
            }
            if ( (*iter)->stringValue() == "false" ) {
                bypassFromRegs_ = false;
                continue;
            }
            throw IllegalParameters(
                __FILE__,__LINE__,__func__, 
                "only true or false value allowed for " +
                BYPASS_FROM_REGS_OPTION);
        }

        if ((*iter)->hasAttribute("name") && 
            (*iter)->stringAttribute("name") == BYPASS_TO_REGS_OPTION) {
            if ( (*iter)->stringValue() == "true" ) {
                bypassToRegs_ = true;
                continue;
            }
            if ( (*iter)->stringValue() == "false" ) {
                bypassToRegs_ = false;
                continue;
            }
            throw IllegalParameters(
                __FILE__,__LINE__,__func__, 
                "only true or false value allowed for " +
                BYPASS_TO_REGS_OPTION);
        }
    }
}

SoftwareBypasser& 
CLBBypasserModule::bypasser() {

    // allow overriding the options using a scheduler command line switch
    
    if (clbs_ == NULL) {
        clbs_ = new CycleLookBackSoftwareBypasser();
    }

    if (Application::verboseLevel() > 0) {
        Application::logStream() 
            << "bypasser: max distance: " << bypassDistance_ << std::endl;
    }
    return *clbs_;
}
/**
 * A short description of the module, usually the module name,
 * in this case "CLBBypasserModule".
 *
 * @return The description as a string.
 */   
std::string
CLBBypasserModule::shortDescription() const {
    return "Helper: CLBBypasserModule";
}

/**
 * Optional longer description of the Module.
 *
 * This description can include usage instructions, details of choice of
 * helper modules, etc.
 *
 * @return The description as a string.
 */
std::string
CLBBypasserModule::longDescription() const {
    std::string answer ="Helper: CLBBypasserModule. ";
    answer += "Implements Cycle look back software bypassing.";
    answer += " Accepts parameter \"swb-lookback-distance\"=<uint>, default is 1.";    
    return answer;
}

const std::string CLBBypasserModule::LOOKBACK_DISTANCE_OPTION = "swb-lookback-distance";
const std::string CLBBypasserModule::NO_DRE_LOOKBACK_DISTANCE_OPTION = "no-dre-swb-lookback-distance";
const std::string CLBBypasserModule::KILL_DEAD_RESULTS_OPTION = "kill-dead-results";
const std::string CLBBypasserModule::BYPASS_FROM_REGS_OPTION = "bypass-from-regs";
const std::string CLBBypasserModule::BYPASS_TO_REGS_OPTION = "bypass-to-regs";
SCHEDULER_PASS(CLBBypasserModule)
