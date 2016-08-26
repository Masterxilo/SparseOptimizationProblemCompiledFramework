:Evaluate: BeginPackage@"SOPCompiled`Private`";

:Begin:
:Function:       f_
:Pattern:        f[input : {___Real}]
:Arguments:      {input}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: f::usage = "the local energy vector computing function"

:Begin:
:Function:       df_
:Pattern:        df[i : _Integer, input : {___Real}]
:Arguments:      {i, input}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: df::usage = "the derivatives along the i-th variable of the local energy vector computing function"

:Begin:
:Function:       nextEven_
:Pattern:        nextEven[i : _Integer]
:Arguments:      {i}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: nextEven::usage = "support even allocation"

:Begin:
:Function:       cs_cumsum_
:Pattern:        cscumsum[p : {___Integer}, c : {___Integer}, n : _Integer]
:Arguments:      {p, c, n}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: cscumsum::usage = "p [0..n] = cumulative sum of c [0..n-1], and then copy p [0..n-1] into c "

:Begin:
:Function:       print_
:Pattern:        print[x : _String]
:Arguments:      {x}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: print::usage = "prints a string to stdout"

:Begin:
:Function:       printd_
:Pattern:        printd[v : {___Integer}]
:Arguments:      {v}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: printd::usage = "dprints a vector of integers, space separated and newline terminated"

:Begin:
:Function:       printv_
:Pattern:        printv[v : {___Real}]
:Arguments:      {v}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: printv::usage = "dprints a vector of doubles, space separated and newline terminated"

:Begin:
:Function:       assertFinite_
:Pattern:        assertFinite[x : {___Real}]
:Arguments:      {x}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: assertFinite::usage = "assert that each element in v is finite"

:Begin:
:Function:       lengthzGet_
:Pattern:        lengthzGet[]
:Arguments:      {}
:ArgumentTypes:  {  }
:ReturnType:     Manual
:End:
:Evaluate: lengthzGet::usage = "lengthz"

:Begin:
:Function:       lengthfzGet_
:Pattern:        lengthfzGet[]
:Arguments:      {}
:ArgumentTypes:  {  }
:ReturnType:     Manual
:End:
:Evaluate: lengthfzGet::usage = "lengthfz"

:Begin:
:Function:       assertEachInRange_
:Pattern:        assertEachInRange[v : {___Integer}, min : _Integer, max : _Integer]
:Arguments:      {v, min, max}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: assertEachInRange::usage = "computes the same as BoolEval[min <= v <= max]"

:Begin:
:Function:       axpyWithReindexing_
:Pattern:        axpyWithReindexing[targetBase : {___Real}, a : _Real, addedValues : {___Real}, targetIndices : {___Integer}]
:Arguments:      {targetBase, a, addedValues, targetIndices}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: axpyWithReindexing::usage = "targetBase[[targetIndices]] += a * addedValues. Repeated indices are not supported, so addedValues cannot be longer than the target.Note that not necessarily all of target is updated (_Inout_updates_, not _Inout_updates_all_)"

:Begin:
:Function:       extract_
:Pattern:        extract[source : {___Real}, sourceIndices : {___Integer}]
:Arguments:      {source, sourceIndices}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: extract::usage = "target = source[[sourceIndices]]. Note that all of target is initialized (_Out_writes_all_)"

:Begin:
:Function:       writeFx_
:Pattern:        writeFx[i : _Integer, val : _Real]
:Arguments:      {i, val}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: writeFx::usage = "F(x)_i = val"

:Begin:
:Function:       readZ_
:Pattern:        readZ[rowz : _Integer]
:Arguments:      {rowz}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: readZ::usage = "z = x[[xIndices[[rowz;;rowz+lengthz-1]]]]"

:Begin:
:Function:       readZandSetFxRow_
:Pattern:        readZandSetFxRow[rowz : _Integer, rowfz : _Integer]
:Arguments:      {rowz, rowfz}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: readZandSetFxRow::usage = "compute and store Fx[[rowfz;;rowfz+lengthfz-1]] = f(z) and return the z = x[[xIndices[[rowz;;rowz+lengthz-1]]]] required for that"

:Begin:
:Function:       setFxRow_
:Pattern:        setFxRow[rowz : _Integer, rowfz : _Integer]
:Arguments:      {rowz, rowfz}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: setFxRow::usage = "compute and store Fx[[rowfz;;rowfz+lengthfz-1]]"

:Begin:
:Function:       buildFx_
:Pattern:        buildFx[]
:Arguments:      {}
:ArgumentTypes:  {  }
:ReturnType:     Manual
:End:
:Evaluate: buildFx::usage = "from the current x, computes F(x)"

:Begin:
:Function:       norm2Fx_
:Pattern:        norm2Fx[]
:Arguments:      {}
:ArgumentTypes:  {  }
:ReturnType:     Manual
:End:
:Evaluate: norm2Fx::usage = "Assuming F(x) is computed, returns ||F(x)||_2^2"

:Begin:
:Function:       addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore_
:Pattern:        addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore[]
:Arguments:      {}
:ArgumentTypes:  {  }
:ReturnType:     Manual
:End:
:Evaluate: addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore::usage = "scales h such that F(x0 + h) < F(x) in the 2-norm and updates x = x0 + hreturns total energy delta achieved which should be negative but might not be when the iteration count is exceeded"

:Begin:
:Function:       getY_
:Pattern:        getY[lengthY : _Integer]
:Arguments:      {lengthY}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: getY::usage = "Extracts from x the elements that are ylengthY must match the length passed at initializationTODO make WSTP support having global variables specify the necessary array length, support non size_t lengthsthen we wouldn't need to supply the redundant lengthY here"

:Begin:
:Function:       buildFxAndJFxAndSolveRepeatedly_
:Pattern:        buildFxAndJFxAndSolveRepeatedly[iterations : _Integer]
:Arguments:      {iterations}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: buildFxAndJFxAndSolveRepeatedly::usage = "using current data, builds JFx (and Fx) and solves the least squares problemthen does a gradient descent stepreapeats this whole process as often as desired"

:Begin:
:Function:       receiveAndPrintOptimizationData_
:Pattern:        receiveAndPrintOptimizationData[lengthz : _Integer, lengthfz : _Integer, x : {___Real}, sparseDerivativeZtoYIndices : {___Integer}, xIndices : {___Integer}, yIndices : {___Integer}]
:Arguments:      {lengthz, lengthfz, x, sparseDerivativeZtoYIndices, xIndices, yIndices}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: receiveAndPrintOptimizationData::usage = "Receives x, sparseDerivativeZtoYIndices, xIndices and yIndices, checks and prints them,emulating arbitrary lengthz, lengthfzNote: lengthz, lengthfz are fixed at compile-time for other functionsThis is a prototyping function that does not allocate or copy anythinguse for testing"

:Begin:
:Function:       makeAndPrintSparseMatrix_
:Pattern:        makeAndPrintSparseMatrix[m : _Integer, n : _Integer, x : {___Real}, ij : {___Integer}]
:Arguments:      {m, n, x, ij}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: makeAndPrintSparseMatrix::usage = "Creates a sparse matrix from a list of values and a list of pairs of (i, j) indices specifying where to put the corresponding values (triplet form)Note: This is a prototyping function without any further purpose"

:Begin:
:Function:       testMain_
:Pattern:        testMain[]
:Arguments:      {}
:ArgumentTypes:  {  }
:ReturnType:     Manual
:End:
:Evaluate: testMain::usage = "collection of some tests"

:Begin:
:Function:       xx43_
:Pattern:        xx43[]
:Arguments:      {}
:ArgumentTypes:  {  }
:ReturnType:     Manual
:End:
:Evaluate: xx43::usage = "sets xx to 43"

:Begin:
:Function:       get42_
:Pattern:        get42[]
:Arguments:      {}
:ArgumentTypes:  {  }
:ReturnType:     Manual
:End:
:Evaluate: get42::usage = "returns the answer to the universe life and everything"

:Begin:
:Function:       add_
:Pattern:        add[x : _Integer, y : _Integer]
:Arguments:      {x, y}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: add::usage = "x + y"

:Begin:
:Function:       addf_
:Pattern:        addf[x : _Real, y : _Real]
:Arguments:      {x, y}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: addf::usage = "x + y with floats"

:Begin:
:Function:       multiout_
:Pattern:        multiout[x : {___Integer}]
:Arguments:      {x}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: multiout::usage = "returns more than one thing: when called via WSTP this will return an Association with all results"

:Begin:
:Function:       receiveOptimizationData_
:Pattern:        receiveOptimizationData[xI : {___Real}, sparseDerivativeZtoYIndicesI : {___Integer}, xIndicesI : {___Integer}, yIndicesI : {___Integer}]
:Arguments:      {xI, sparseDerivativeZtoYIndicesI, xIndicesI, yIndicesI}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: receiveOptimizationData::usage = "Receives x, sparseDerivativeZtoYIndices, xIndices and yIndicesAppropriately sized vectors for receiving these data items are newly allocated in __managed__ memory, hence this is a CPU only function"

:Begin:
:Function:       receiveOptimizationDataBuildFxAndJFxAndSolveRepeatedly_
:Pattern:        receiveOptimizationDataBuildFxAndJFxAndSolveRepeatedly[xI : {___Real}, sparseDerivativeZtoYIndicesI : {___Integer}, xIndicesI : {___Integer}, yIndicesI : {___Integer}, iterations : _Integer]
:Arguments:      {xI, sparseDerivativeZtoYIndicesI, xIndicesI, yIndicesI, iterations}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: receiveOptimizationDataBuildFxAndJFxAndSolveRepeatedly::usage = "Receives x, sparseDerivativeZtoYIndices, xIndices and yIndicesAppropriately sized vectors for receiving these data items is allocated in __managed__ memory, hence this is a CPU only functioncurrently also builds F(x), JF(x), but that could also be done on the GPU laterit also calls solve, because J is built in local memory so it would be lost later"

:Begin:
:Function:       f_CUDA
:Pattern:        fCUDA[gridDim_Integer, blockDim_Integer, input : {___Real}]
:Arguments:      {gridDim, blockDim, input}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: fCUDA::usage = "the local energy vector computing function"

:Begin:
:Function:       df_CUDA
:Pattern:        dfCUDA[gridDim_Integer, blockDim_Integer, i : _Integer, input : {___Real}]
:Arguments:      {gridDim, blockDim, i, input}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: dfCUDA::usage = "the derivatives along the i-th variable of the local energy vector computing function"

:Begin:
:Function:       nextEven_CUDA
:Pattern:        nextEvenCUDA[gridDim_Integer, blockDim_Integer, i : _Integer]
:Arguments:      {gridDim, blockDim, i}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: nextEvenCUDA::usage = "support even allocation"

:Begin:
:Function:       cs_cumsum_CUDA
:Pattern:        cscumsumCUDA[gridDim_Integer, blockDim_Integer, p : {___Integer}, c : {___Integer}, n : _Integer]
:Arguments:      {gridDim, blockDim, p, c, n}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: cscumsumCUDA::usage = "p [0..n] = cumulative sum of c [0..n-1], and then copy p [0..n-1] into c "

:Begin:
:Function:       print_CUDA
:Pattern:        printCUDA[gridDim_Integer, blockDim_Integer, x : _String]
:Arguments:      {gridDim, blockDim, x}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: printCUDA::usage = "prints a string to stdout"

:Begin:
:Function:       printd_CUDA
:Pattern:        printdCUDA[gridDim_Integer, blockDim_Integer, v : {___Integer}]
:Arguments:      {gridDim, blockDim, v}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: printdCUDA::usage = "dprints a vector of integers, space separated and newline terminated"

:Begin:
:Function:       printv_CUDA
:Pattern:        printvCUDA[gridDim_Integer, blockDim_Integer, v : {___Real}]
:Arguments:      {gridDim, blockDim, v}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: printvCUDA::usage = "dprints a vector of doubles, space separated and newline terminated"

:Begin:
:Function:       assertFinite_CUDA
:Pattern:        assertFiniteCUDA[gridDim_Integer, blockDim_Integer, x : {___Real}]
:Arguments:      {gridDim, blockDim, x}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: assertFiniteCUDA::usage = "assert that each element in v is finite"

:Begin:
:Function:       lengthzGet_CUDA
:Pattern:        lengthzGetCUDA[gridDim_Integer, blockDim_Integer]
:Arguments:      {gridDim, blockDim}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: lengthzGetCUDA::usage = "lengthz"

:Begin:
:Function:       lengthfzGet_CUDA
:Pattern:        lengthfzGetCUDA[gridDim_Integer, blockDim_Integer]
:Arguments:      {gridDim, blockDim}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: lengthfzGetCUDA::usage = "lengthfz"

:Begin:
:Function:       assertEachInRange_CUDA
:Pattern:        assertEachInRangeCUDA[gridDim_Integer, blockDim_Integer, v : {___Integer}, min : _Integer, max : _Integer]
:Arguments:      {gridDim, blockDim, v, min, max}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: assertEachInRangeCUDA::usage = "computes the same as BoolEval[min <= v <= max]"

:Begin:
:Function:       axpyWithReindexing_CUDA
:Pattern:        axpyWithReindexingCUDA[gridDim_Integer, blockDim_Integer, targetBase : {___Real}, a : _Real, addedValues : {___Real}, targetIndices : {___Integer}]
:Arguments:      {gridDim, blockDim, targetBase, a, addedValues, targetIndices}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: axpyWithReindexingCUDA::usage = "targetBase[[targetIndices]] += a * addedValues. Repeated indices are not supported, so addedValues cannot be longer than the target.Note that not necessarily all of target is updated (_Inout_updates_, not _Inout_updates_all_)"

:Begin:
:Function:       extract_CUDA
:Pattern:        extractCUDA[gridDim_Integer, blockDim_Integer, source : {___Real}, sourceIndices : {___Integer}]
:Arguments:      {gridDim, blockDim, source, sourceIndices}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: extractCUDA::usage = "target = source[[sourceIndices]]. Note that all of target is initialized (_Out_writes_all_)"

:Begin:
:Function:       writeFx_CUDA
:Pattern:        writeFxCUDA[gridDim_Integer, blockDim_Integer, i : _Integer, val : _Real]
:Arguments:      {gridDim, blockDim, i, val}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: writeFxCUDA::usage = "F(x)_i = val"

:Begin:
:Function:       readZ_CUDA
:Pattern:        readZCUDA[gridDim_Integer, blockDim_Integer, rowz : _Integer]
:Arguments:      {gridDim, blockDim, rowz}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: readZCUDA::usage = "z = x[[xIndices[[rowz;;rowz+lengthz-1]]]]"

:Begin:
:Function:       readZandSetFxRow_CUDA
:Pattern:        readZandSetFxRowCUDA[gridDim_Integer, blockDim_Integer, rowz : _Integer, rowfz : _Integer]
:Arguments:      {gridDim, blockDim, rowz, rowfz}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: readZandSetFxRowCUDA::usage = "compute and store Fx[[rowfz;;rowfz+lengthfz-1]] = f(z) and return the z = x[[xIndices[[rowz;;rowz+lengthz-1]]]] required for that"

:Begin:
:Function:       setFxRow_CUDA
:Pattern:        setFxRowCUDA[gridDim_Integer, blockDim_Integer, rowz : _Integer, rowfz : _Integer]
:Arguments:      {gridDim, blockDim, rowz, rowfz}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: setFxRowCUDA::usage = "compute and store Fx[[rowfz;;rowfz+lengthfz-1]]"

:Begin:
:Function:       buildFx_CUDA
:Pattern:        buildFxCUDA[gridDim_Integer, blockDim_Integer]
:Arguments:      {gridDim, blockDim}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: buildFxCUDA::usage = "from the current x, computes F(x)"

:Begin:
:Function:       norm2Fx_CUDA
:Pattern:        norm2FxCUDA[gridDim_Integer, blockDim_Integer]
:Arguments:      {gridDim, blockDim}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: norm2FxCUDA::usage = "Assuming F(x) is computed, returns ||F(x)||_2^2"

:Begin:
:Function:       addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore_CUDA
:Pattern:        addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBeforeCUDA[gridDim_Integer, blockDim_Integer]
:Arguments:      {gridDim, blockDim}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBeforeCUDA::usage = "scales h such that F(x0 + h) < F(x) in the 2-norm and updates x = x0 + hreturns total energy delta achieved which should be negative but might not be when the iteration count is exceeded"

:Begin:
:Function:       getY_CUDA
:Pattern:        getYCUDA[gridDim_Integer, blockDim_Integer, lengthY : _Integer]
:Arguments:      {gridDim, blockDim, lengthY}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: getYCUDA::usage = "Extracts from x the elements that are ylengthY must match the length passed at initializationTODO make WSTP support having global variables specify the necessary array length, support non size_t lengthsthen we wouldn't need to supply the redundant lengthY here"

:Begin:
:Function:       buildFxAndJFxAndSolveRepeatedly_CUDA
:Pattern:        buildFxAndJFxAndSolveRepeatedlyCUDA[gridDim_Integer, blockDim_Integer, iterations : _Integer]
:Arguments:      {gridDim, blockDim, iterations}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: buildFxAndJFxAndSolveRepeatedlyCUDA::usage = "using current data, builds JFx (and Fx) and solves the least squares problemthen does a gradient descent stepreapeats this whole process as often as desired"

:Begin:
:Function:       receiveAndPrintOptimizationData_CUDA
:Pattern:        receiveAndPrintOptimizationDataCUDA[gridDim_Integer, blockDim_Integer, lengthz : _Integer, lengthfz : _Integer, x : {___Real}, sparseDerivativeZtoYIndices : {___Integer}, xIndices : {___Integer}, yIndices : {___Integer}]
:Arguments:      {gridDim, blockDim, lengthz, lengthfz, x, sparseDerivativeZtoYIndices, xIndices, yIndices}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: receiveAndPrintOptimizationDataCUDA::usage = "Receives x, sparseDerivativeZtoYIndices, xIndices and yIndices, checks and prints them,emulating arbitrary lengthz, lengthfzNote: lengthz, lengthfz are fixed at compile-time for other functionsThis is a prototyping function that does not allocate or copy anythinguse for testing"

:Begin:
:Function:       makeAndPrintSparseMatrix_CUDA
:Pattern:        makeAndPrintSparseMatrixCUDA[gridDim_Integer, blockDim_Integer, m : _Integer, n : _Integer, x : {___Real}, ij : {___Integer}]
:Arguments:      {gridDim, blockDim, m, n, x, ij}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: makeAndPrintSparseMatrixCUDA::usage = "Creates a sparse matrix from a list of values and a list of pairs of (i, j) indices specifying where to put the corresponding values (triplet form)Note: This is a prototyping function without any further purpose"

:Begin:
:Function:       testMain_CUDA
:Pattern:        testMainCUDA[gridDim_Integer, blockDim_Integer]
:Arguments:      {gridDim, blockDim}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: testMainCUDA::usage = "collection of some tests"

:Begin:
:Function:       xx43_CUDA
:Pattern:        xx43CUDA[gridDim_Integer, blockDim_Integer]
:Arguments:      {gridDim, blockDim}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: xx43CUDA::usage = "sets xx to 43"

:Begin:
:Function:       get42_CUDA
:Pattern:        get42CUDA[gridDim_Integer, blockDim_Integer]
:Arguments:      {gridDim, blockDim}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: get42CUDA::usage = "returns the answer to the universe life and everything"

:Begin:
:Function:       add_CUDA
:Pattern:        addCUDA[gridDim_Integer, blockDim_Integer, x : _Integer, y : _Integer]
:Arguments:      {gridDim, blockDim, x, y}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: addCUDA::usage = "x + y"

:Begin:
:Function:       addf_CUDA
:Pattern:        addfCUDA[gridDim_Integer, blockDim_Integer, x : _Real, y : _Real]
:Arguments:      {gridDim, blockDim, x, y}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: addfCUDA::usage = "x + y with floats"

:Begin:
:Function:       multiout_CUDA
:Pattern:        multioutCUDA[gridDim_Integer, blockDim_Integer, x : {___Integer}]
:Arguments:      {gridDim, blockDim, x}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: multioutCUDA::usage = "returns more than one thing: when called via WSTP this will return an Association with all results"

:Begin:
:Function:       dprintEnabled_get
:Pattern:        dprintEnabledGet[]
:Arguments:      {}
:ArgumentTypes:  { }
:ReturnType:     Manual
:End:
:Evaluate: dprintEnabledGet::usage = "if true, dprintf writes to stdout, otherwise dprintf does nothingIt would be more efficient to compile with dprintf defined to nothing of courseDefault: true"

:Begin:
:Function:       lengthP_get
:Pattern:        lengthPGet[]
:Arguments:      {}
:ArgumentTypes:  { }
:ReturnType:     Manual
:End:
:Evaluate: lengthPGet::usage = "amount of 'points' at which the function f is evaluated.lengthP * lengthz is the length of xIndices, and sparseDerivativeZtoYIndices contains lengthP sequences of the form (k [k many z indices] [k many y indices]) "

:Begin:
:Function:       xx_get
:Pattern:        xxGet[]
:Arguments:      {}
:ArgumentTypes:  { }
:ReturnType:     Manual
:End:
:Evaluate: xxGet::usage = "xx"

:Begin:
:Function:       a_get
:Pattern:        aGet[]
:Arguments:      {}
:ArgumentTypes:  { }
:ReturnType:     Manual
:End:
:Evaluate: aGet::usage = "a"

:Begin:
:Function:       b_get
:Pattern:        bGet[]
:Arguments:      {}
:ArgumentTypes:  { }
:ReturnType:     Manual
:End:
:Evaluate: bGet::usage = "b"

:Begin:
:Function:       yy_get
:Pattern:        yyGet[]
:Arguments:      {}
:ArgumentTypes:  { }
:ReturnType:     Manual
:End:
:Evaluate: yyGet::usage = "yy"

:Begin:
:Function:       x_get
:Pattern:        xGet[]
:Arguments:      {}
:ArgumentTypes:  { }
:ReturnType:     Manual
:End:
:Evaluate: xGet::usage = "stores the current data vector 'x' which is updated to reduce the energy ||F(x)||^2"

:Begin:
:Function:       minusFx_get
:Pattern:        minusFxGet[]
:Arguments:      {}
:ArgumentTypes:  { }
:ReturnType:     Manual
:End:
:Evaluate: minusFxGet::usage = "-F(x)"

:Begin:
:Function:       h_get
:Pattern:        hGet[]
:Arguments:      {}
:ArgumentTypes:  { }
:ReturnType:     Manual
:End:
:Evaluate: hGet::usage = "h, the update to y (subset of x, the parameters currently optimized over)"

:Begin:
:Function:       yIndices_get
:Pattern:        yIndicesGet[]
:Arguments:      {}
:ArgumentTypes:  { }
:ReturnType:     Manual
:End:
:Evaluate: yIndicesGet::usage = "the indices into x that indicate where the y areneeded to write out the final update h to the parameters"

:Begin:
:Function:       dprintEnabled_set
:Pattern:        dprintEnabledSet[dprintEnabled : _Integer]
:Arguments:      {dprintEnabled}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: dprintEnabledSet::usage = "if true, dprintf writes to stdout, otherwise dprintf does nothingIt would be more efficient to compile with dprintf defined to nothing of courseDefault: true"

:Begin:
:Function:       lengthP_set
:Pattern:        lengthPSet[lengthP : _Integer]
:Arguments:      {lengthP}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: lengthPSet::usage = "amount of 'points' at which the function f is evaluated.lengthP * lengthz is the length of xIndices, and sparseDerivativeZtoYIndices contains lengthP sequences of the form (k [k many z indices] [k many y indices]) "

:Begin:
:Function:       xx_set
:Pattern:        xxSet[xx : _Integer]
:Arguments:      {xx}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: xxSet::usage = "xx"

:Begin:
:Function:       a_set
:Pattern:        aSet[a : _Real]
:Arguments:      {a}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: aSet::usage = "a"

:Begin:
:Function:       b_set
:Pattern:        bSet[b : _Real]
:Arguments:      {b}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: bSet::usage = "b"

:Begin:
:Function:       yy_set
:Pattern:        yySet[yy : _Real]
:Arguments:      {yy}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: yySet::usage = "yy"

:Begin:
:Function:       x_set
:Pattern:        xSet[x : {___Real}]
:Arguments:      {x}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: xSet::usage = "stores the current data vector 'x' which is updated to reduce the energy ||F(x)||^2"

:Begin:
:Function:       minusFx_set
:Pattern:        minusFxSet[minusFx : {___Real}]
:Arguments:      {minusFx}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: minusFxSet::usage = "-F(x)"

:Begin:
:Function:       h_set
:Pattern:        hSet[h : {___Real}]
:Arguments:      {h}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: hSet::usage = "h, the update to y (subset of x, the parameters currently optimized over)"

:Begin:
:Function:       yIndices_set
:Pattern:        yIndicesSet[yIndices : {___Integer}]
:Arguments:      {yIndices}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: yIndicesSet::usage = "the indices into x that indicate where the y areneeded to write out the final update h to the parameters"
:Evaluate: EndPackage[];
