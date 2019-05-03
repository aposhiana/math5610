import matplotlib.pyplot as pyplot

pyplot.plot([10, 50, 100, 200, 500, 800, 1000],[7.61e-05, 0.0030244, 0.0123754, 0.106681, 1.54027, 6.16774, 11.0862], label='Gaussian Elimination', color='red')
pyplot.plot([10, 50, 100, 200, 500, 800, 1000],[0.0009113, 0.0029411, 0.010248, 0.0301007, 0.391178, 0.475738, 0.795324], label='Jacobi Iteration', color='green')
pyplot.plot([10, 50, 100, 200, 500, 800, 1000],[0.000578, 0.001161, 0.0048755, 0.0184433, 0.259531, 0.413726, 0.514353], label='Gauss-Seidel', color='blue')

pyplot.xlabel('Matrix size (number of equations and unknowns)')
pyplot.ylabel('Time (seconds)') 
pyplot.legend()
pyplot.show() 
