package com.olegchir.ow;

import java.awt.*;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.StringSelection;
import java.awt.image.BufferedImage;
import java.awt.image.Raster;

public class Main {

    public static void main(String[] args) {
        String result = "0";

        try {
            BufferedImage image = new Robot().createScreenCapture(new Rectangle(Toolkit.getDefaultToolkit().getScreenSize()));

            int height = image.getHeight();
            int width = image.getWidth();
            Raster data = image.getData();

            boolean sameColor = true;

            int[] proto = new int[]{1, 1, 1};
            int y = height - 1;
            for (int x = 0; x < width; x++) {
                int[] currPixel = data.getPixel(x, y, new int[3]);
                if (
                        (currPixel[0] != proto[0]) ||
                        (currPixel[1] != proto[1]) ||
                        (currPixel[2] != proto[2])
                ) {
                    sameColor = false;
                    break;
                }
            }

            if (sameColor) {
                result = "1";
            } else {
                result = "0";
            }

        } catch (AWTException e) {
            e.printStackTrace();
        }

        StringSelection selection = new StringSelection(result);
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        clipboard.setContents(selection, selection);

        System.out.print(result);
    }
}
