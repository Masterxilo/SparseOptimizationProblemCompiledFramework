Status: Compiles and runs on PAULSPC only. Available from Within Mathematica via SOPCompiled* functions.

* Code generation in RIFunction not perfect.
* Latest SOPD infrastructure contained in InfiniTAM projects, separate from here.

-----

04.11.2016 (Patrick's birthday) 

Clean up via 

    Uninstall@SOPCompiled$InstalledExe[]
    SOPCompiledClear[]

 to ensure that compilation of modules works.
Use TestDepersistHeldDefContainingByPersistedNames@SOPCompiledPrepare to find some tests. 
Run them with ReleaseHoldAssociation@
These all pass.

Right now does not even build: Changes in paul.h. Fixed

individual API function health:

Good:
SOPCompiledPrepare must start out with this
SOPCompiled should be black symbol (recognized identifier)
SOPCompiledClear
SOPCompiledOptimizeMultiple
SOPCompiledOptimize
SOPCompiled$InstalledExe not quite clear that (and why) only one SOPCompiled exe can be installed.
    Ah, because they share the low-level API, this is not instance specific. WSTP communication happens via symbols, which can only have a binding to one running program at a time.
SOPCompiled$InstalledLink
    Still returns something when program was killed
SOPCompiledEnsureInstalled
SOPCompiledEnsureUninstalled
SOPCompiled$FrameworkDirectory

internal: (TODO maybe use a different naming)
SOPCompiledOptimizePreprocessedMultiple
SOPCompiledOptimizePreprocessedSubmitPartition
SOPCompiledMakeRIFunction

Bad:

Untested:
SOPCompiledFlattenSparseDerivativeZtoYIndices
SOPCompiledOptimizePreprocessed

