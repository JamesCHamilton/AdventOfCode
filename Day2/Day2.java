package Day2;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;

public class Day2 {

    public static void main(String[] args) {
        int testResult = SafetyTracker("C:/Users/meela/Downloads/Personal-Projects/AdventOfCode/Day2/Day2TestInput.txt");
        int result = SafetyTracker("C:/Users/meela/Downloads/Personal-Projects/AdventOfCode/Day2/Day2Input.txt");
        System.out.println(testResult);
        System.out.println(result);
    } 

    public static Boolean isSafe(String[] currLine){
                
            Boolean isIncreasing = false;
            Boolean isDecreasing = false;
            int length = currLine.length;

            for (int i = 0; i< length - 1; i++){
                int difference = (Integer.parseInt(currLine[i]) - Integer.parseInt(currLine[i+1]));
                if(Math.abs(difference) > 3 || Math.abs(difference) < 1){
                    return false;
                }

                if( i == 0){
                    if(difference < 0){
                        isDecreasing = true;
                    }else if(difference > 0){
                        isIncreasing = true;
                    }
                }else{
                    if((isIncreasing && difference < 0) || (isDecreasing && difference > 0)){
                        return false;
                    }
                }

            }
            return true;

    }

    public static int SafetyTracker(String filepath){
        BufferedReader reader;
        int safe = 0;
        
        try {

            reader = new BufferedReader(new FileReader(filepath));
            String line = reader.readLine();
            
            while(line != null){
                String[] currLine = line.split("\\s+");
                int length = currLine.length;

                if(isSafe(currLine)){
                    System.out.println(Arrays.toString(currLine) + "is safe");
                    safe++;
                }else{

                    Boolean canBeFixed = false;
                    for(int i = 0; i <length; i++){
                        String[] modifiedLine = new String[length - 1];
                        int index = 0;

                        for(int j = 0; j < length; j++){
                            if( j != i){
                                modifiedLine[index++] = currLine[j];
                            }
                        }
                        if(isSafe(modifiedLine)){
                            System.out.println(Arrays.toString(currLine) + "can be fixed");
                            canBeFixed = true;
                            break;
                        }
                    }
                    
                    if(canBeFixed){
                        safe++;
                    }
                }
                line = reader.readLine(); 
            }

            reader.close();
            
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }

        return safe;
    }

}