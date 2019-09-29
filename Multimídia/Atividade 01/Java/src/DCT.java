
public class DCT {

    public double[][] apply(double[][] input, int numrows, int numcols) {
        double[][] result = new double[numrows][numcols];

        for (int count = 0; count < input.length; count++) {
            result[count] = this.dct(input[count], numrows, numcols);
        }

        return result;
    }

    public double[] dct(double[] input, int numrows, int numcols) {
        double[] result = new double[numrows];

        int SIZE = numcols;

        for (int k = 0; k < SIZE; k++) {
            double sum = 0.0;
            for (int n = 0; n < SIZE; n++) {
                sum += input[n] * Math.cos((Math.PI * (2.0 * n + 1.0) * k) / (2.0 * SIZE));
            }
            double alfa = k == 0 ? Math.sqrt(1.0 / SIZE) : Math.sqrt(2.0 / SIZE);
            result[k] = (alfa * sum);
        }

        return result;
    }

    public double[][] apply_quantization(double[][] input, int numrows, int numcols) {
        double[][] result = new double[numrows][numcols];

        int size_block = 8;
        for (int i = 0; i < size_block; i++) {
            for (int j = 0; j < size_block; j++) {
                for (int k = 0; k < size_block; k++) {
                    int c = (int) Math.round(input[size_block * i + j][size_block * i + k] / Utils.quantization_50[i][j]);
                    result[size_block * i + j][size_block * i + k] = c;
                }
            }
        }

        return result;
    }

}
