/*
    Copyright (c) 2002-2010 Tampere University of Technology.

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
 * @file GhdlSimulator.hh
 *
 * Declaration of GhdlSimulator
 *
 * @author Otto Esko 2010 (otto.esko-no.spam-tut.fi)
 * @note rating: red
 */

#ifndef TTA_GHDL_SIMULATOR_HH
#define TTA_GHDL_SIMULATOR_HH

#include <string>
#include <vector>
#include "ImplementationSimulator.hh"

class GhdlSimulator : public ImplementationSimulator {
public:
    GhdlSimulator(
        std::string tbFile, std::vector<std::string> hdlFiles, bool verbose);

    virtual ~GhdlSimulator();

    virtual bool compile(std::vector<std::string>& errors);
    
    virtual bool simulate(std::vector<std::string>& errors);

private:
    bool importFile(std::string file, std::vector<std::string>& errors);

    bool compileDesign(std::vector<std::string>& errors);

};

#endif