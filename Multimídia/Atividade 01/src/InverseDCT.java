
public class InverseDCT {

    public double[][] apply(double[][] input, int numrows, int numcols) {

        double[][] result = new double[numrows][numcols];
        
        for (int count = 0; count < input.length; count++) {
            result[count] = this.inverse_dct(input[count], numrows, numcols);
        }

        return result;
    }

    public double[] inverse_dct(double[] input, int numrows, int numcols) {
        double[] result = new double[numrows];

        int SIZE = numcols;

        for (int n = 0; n < input.length; n++) {
            double sum = 0;
            for (int k = 0; k < SIZE; k++) {
                double alfa = k == 0 ? Math.sqrt(1.0 / SIZE) : Math.sqrt(2.0 / SIZE);
                sum += alfa * input[k] * Math.cos((Math.PI * (2.0 * n + 1.0) * k) / (2.0 * SIZE));
            }

            result[n] = sum;
        }
        return result;
    }
    
    public double[][] apply_quantization(double[][] input, int numrows, int numcols) {
        double[][] result = new double[numrows][numcols];
        
        return result;
    }
}
