
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Scanner;

public class Utils {
    
    public static double[][] read_image() throws FileNotFoundException{
        File file = new File(new File("").getAbsoluteFile() + "/image.pgm");
        Scanner sc = new Scanner(file);
        
        String version = sc.nextLine();
        String comments = sc.nextLine();
        int numrows = Integer.parseInt(sc.next());
        int numcols = Integer.parseInt(sc.next());
        int number_bits = Integer.parseInt(sc.next());
        
        Utils.print_info(version, comments, numrows, numcols);

        double original_image[][] = new double[numrows][numcols];

        for (int i = 0; i < numrows; i++) {
            for (int j = 0; j < numcols; j++) {
                original_image[i][j] = Double.parseDouble(sc.next());
            }
        }
        return original_image;
    }

    public static void print_image(double[][] image, int numrows, int numcols) {
        System.out.println();
        System.out.println("==========================");
        for (int i = 0; i < numrows; i++) {
            for (int j = 0; j < numcols; j++) {
                System.out.print(image[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println("==========================");
    }
    
    public static void print_info(String version, String comments, int numrows, int numcols) {
        System.out.println("== Welcome to DCT algorithm ==");
        System.out.println("Version file: " + version);
        System.out.println("Comments: " + comments);
        System.out.println("Size:" + numrows + "x" + numcols);
        System.out.println("Number bits: " + 255);
        System.out.println("==============================");
        System.out.println();
        System.out.println();
    }

    public static void export_to_file(double[][] image, int numrows, int numcols) throws FileNotFoundException, UnsupportedEncodingException {
        File currentDir = new File("");
        System.out.println("== Exporting image DCT to file ==");
        PrintWriter writer = new PrintWriter(currentDir.getAbsoluteFile() + "/image_dct.pgm", "UTF-8");
        writer.println("P2");
        writer.println("# DCT and Inverse DCT algorithm");
        writer.println(numrows + " " + numcols);
        writer.println(255);
        for (int i = 0; i < numrows; i++) {
            for (int j = 0; j < numcols; j++) {
                //writer.println((int)Math.round(image[i][j]));
                //writer.println(image[i][j]);
                writer.println((Math.floor((image[i][j]) * 100) / 100));
            }
        }
        writer.close();
        System.out.println("== Finished ==");
    }
}
