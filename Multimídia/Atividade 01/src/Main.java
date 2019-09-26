import java.io.FileNotFoundException;
import java.io.UnsupportedEncodingException;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {      
        double[][] original_image = Utils.read_image();
        
        int numrows = original_image.length;
        int numcols = original_image[0].length;
        
        double[][] copy_image = Arrays.copyOf(original_image, original_image.length);
        
        long startTime = System.currentTimeMillis();
                
        DCT dct = new DCT();
        double[][] image_dct = dct.apply(copy_image, numrows, numcols);
        
        double[][] copy_dct = Arrays.copyOf(image_dct, image_dct.length);
        double[][] dct_quantization = dct.apply_quantization(copy_dct, numrows, numcols);
        
        InverseDCT dct_inverse = new InverseDCT();
        double[][] image_dct_inverse = dct_inverse.apply(image_dct, numrows, numcols);
        
        Utils.print_image(dct_quantization, numrows, numcols);
        //Utils.print_image(original_image, numrows, numcols);
        //Utils.print_image(image_dct, numrows, numcols);
        //Utils.print_image(image_dct_inverse, numrows, numcols);
        
        //Utils.export_to_file(image_dct_inverse, numrows, numcols);
        
        long endTime = System.currentTimeMillis();
        
        System.out.println("Time: " + (endTime - startTime) + " milliseconds");
    }
}
