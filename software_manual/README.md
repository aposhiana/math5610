## Software Manual
by Andrew Aposhian

### Table of Contents

* **Basic computional math routines**
    * MachineEpsilon.hpp
        * [getMachineEpsilon](./getMachineEpsilon.md)
        * [getDoubleMachineEpsilon](./getDoubleMachineEpsilon.md)
* **Basic linear algebra routines**
    * [Array\<T\>](./Array.md)
    * [DenseArray\<T\>](./DenseArray.md)
        * [makeRandomSymmetric.md](./makeRandomSymmetric.md)
        * [makeRandomDD.md](./makeRandomDD.md)
        * [makeRandomSymmetricDD.md](./makeRandomSymmetricDD.md)
    * [Vector\<T\>](./Vector.md)
    * ArrayUtils.hpp
        * [add](./add.md)
        * [multiply](./multiply.md)
        * [dot](./dot.md)
        * [cross](./cross.md)
        * [matmul](./matmul.md)
        * [transpose](./transpose.md)
        * [makeRandomRawArray](./makeRandomRawArray.md)
        * [getRandomSPDArray](./getRandomSPDArray)
    * VectorNorms.hpp
        * [absoluteError](./absoluteError.md)
        * [relativeError](./relativeError.md)
        * [l1Norm](./l1Norm.md)
        * [l2Norm](./l2Norm.md)
        * [infNorm](./infNorm.md)
        * [l1NormAbsoluteError](l1NormAbsoluteError.md)
        * [l2NormAbsoluteError](l2NormAbsoluteError.md)
        * [infNormAbsoluteError](infNormAbsoluteError.md)
    * MatrixNorms.hpp
        * [matrix1Norm](./matrix1Norm.md)
        * [matrixInfNorm](./matrixInfNorm.md)
        * [estimate2NormConditionNumber](./estimate2NormConditionNumber.md)
* **Solution of Linear Systems**
    * [solveLinearDiagonalSystem](solveLinearDiagonalSystem.md)
    * [backsub](backsub.md)
    * [forwardsub](forwardsub.md)
    * [rowReduce](rowReduce.md)
    * [solveLinearSystem](solveLinearSystem.md)
    * [solveLinearSystemInline](solveLinearSystemInline.md)
    * [lu](lu.md)
    * [luSolve](luSolve.md)
    * [cholesky](cholesky.md)
    * [solveNormalEquation](solveNormalEquation.md)
    * [jacobiSolve](jacobiSolve.md)
    * [gaussSeidelSolve](gaussSeidelSolve.md)
    * [steepestDescentSolve](steepestDescentSolve.md)
    * [cg](cg.md)
    * [squareClassicalGramSchmidt](squareClassicalGramSchmidt.md)
    * [squareModifiedGramSchmidt](squareModifiedGramSchmidt.md)
    * [qrSolve](qrSolve.md)
* **Eigenvalue Solvers**
    * [powerEigenSolve](powerEigenSolve.md)
    * [inverseEigenSolve](inverseEigenSolve.md)
    * [inverseEigenJacobiSolve](inverseEigenJacobiSolve.md)
    * [rayleighEigenSolve](rayleighEigenSolve.md)
