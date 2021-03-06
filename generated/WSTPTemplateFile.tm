:Evaluate: $oldContextPath = $ContextPath; $ContextPath = {"System`"};
:Evaluate: Begin@"SOPCompiled`Private`";
:Evaluate: ClearAll@"SOPCompiled`Private`*";
:Begin:
:Function:       f_
:Pattern:        f[input : {___Real}]
:Arguments:      {input}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: f::usage = "the local energy fvector computing function"

:Begin:
:Function:       df_
:Pattern:        df[i : _Integer, input : {___Real}]
:Arguments:      {i, input}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: df::usage = "the derivatives along the i-th variable of the local energy fvector computing function"

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
:Evaluate: printd::usage = "dprints a fvector of integers, space separated and newline terminated"

:Begin:
:Function:       printv_
:Pattern:        printv[v : {___Real}]
:Arguments:      {v}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: printv::usage = "dprints a fvector of doubles, space separated and newline terminated"

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
:Function:       getY_
:Pattern:        getY[partition : _Integer, lengthY : _Integer]
:Arguments:      {partition, lengthY}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: getY::usage = "Extracts from x the elements that are ylengthY must match the length passed at initializationTODO make WSTP support having global variables specify the necessary array length, support non size_t lengthsthen we wouldn't need to supply the redundant lengthY here"

:Begin:
:Function:       buildFxAndJFxAndSolveRepeatedly_
:Pattern:        buildFxAndJFxAndSolveRepeatedly[partition : _Integer, iterations : _Integer]
:Arguments:      {partition, iterations}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: buildFxAndJFxAndSolveRepeatedly::usage = "using current data, builds JFx (and Fx) and solves the least squares problemthen does a gradient descent stepreapeats this whole process as often as desired"

:Begin:
:Function:       buildFxAndJFxAndSolveRepeatedlyThreadIdPartition_
:Pattern:        buildFxAndJFxAndSolveRepeatedlyThreadIdPartition[iterations : _Integer]
:Arguments:      {iterations}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: buildFxAndJFxAndSolveRepeatedlyThreadIdPartition::usage = "buildFxAndJFxAndSolveRepeatedly on the partition given by linear_global_threadId.does nothing when linear_global_threadId is >= partitionsTODO this should be the block id, threads in the same block should cooperate in the same partition"

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
:Evaluate: makeAndPrintSparseMatrix::usage = "Creates a sparse matrix from a list of values and a list of pairs of (i, j) indices specifying where to put the corresponding values (triplet form) then cs_prints it to stdout both in column form and vanilla.The matrix should be fairly small because the required intermediate storage is on the stack.Note: This is a prototyping function without any further purpose"

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
:Function:       mainc_
:Pattern:        mainc[]
:Arguments:      {}
:ArgumentTypes:  {  }
:ReturnType:     Manual
:End:
:Evaluate: mainc::usage = ""

:Begin:
:Function:       setPartitions_
:Pattern:        setPartitions[newPartitionsCount : _Integer]
:Arguments:      {newPartitionsCount}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: setPartitions::usage = "set the amount of partitions"

:Begin:
:Function:       receiveSharedOptimizationData_
:Pattern:        receiveSharedOptimizationData[xI : {___Real}]
:Arguments:      {xI}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: receiveSharedOptimizationData::usage = "Receives x"

:Begin:
:Function:       receiveOptimizationData_
:Pattern:        receiveOptimizationData[partition : _Integer, sparseDerivativeZtoYIndicesI : {___Integer}, xIndicesI : {___Integer}, yIndicesI : {___Integer}]
:Arguments:      {partition, sparseDerivativeZtoYIndicesI, xIndicesI, yIndicesI}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: receiveOptimizationData::usage = "Receives sparseDerivativeZtoYIndices, xIndices and yIndicesAppropriately sized vectors for receiving these data items are newly allocated in __managed__ memory, hence this is a CPU only function"

:Begin:
:Function:       dprintEnabled_get
:Pattern:        dprintEnabledGet[]
:Arguments:      {}
:ArgumentTypes:  { }
:ReturnType:     Manual
:End:
:Evaluate: dprintEnabledGet::usage = "if true, dprintf writes to stdout, otherwise dprintf does nothingIt would be more efficient to compile with dprintf defined to nothing of courseDefault: true"

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
:Evaluate: xGet::usage = "stores the current data fvector 'x' which is updated to reduce the energy ||F(x)||^2"

:Begin:
:Function:       dprintEnabled_set
:Pattern:        dprintEnabledSet[dprintEnabled : _Integer]
:Arguments:      {dprintEnabled}
:ArgumentTypes:  { Manual }
:ReturnType:     Manual
:End:
:Evaluate: dprintEnabledSet::usage = "if true, dprintf writes to stdout, otherwise dprintf does nothingIt would be more efficient to compile with dprintf defined to nothing of courseDefault: true"

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
:Evaluate: xSet::usage = "stores the current data fvector 'x' which is updated to reduce the energy ||F(x)||^2"

:Evaluate: End[];
:Evaluate: $ContextPath = $oldContextPath;
