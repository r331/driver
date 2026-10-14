// Ghidra headless: export function list + decompiled C
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import java.io.*;
public class ExportAll extends GhidraScript {
  public void run() throws Exception {
    String outDir = getScriptArgs()[0];
    DecompInterface d = new DecompInterface(); d.openProgram(currentProgram);
    PrintWriter csv = new PrintWriter(new FileWriter(outDir+"/functions.csv"));
    PrintWriter c = new PrintWriter(new FileWriter(outDir+"/Game_decomp.c"));
    csv.println("address,name,size,library");
    FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
    int n=0, ok=0;
    while (it.hasNext() && !monitor.isCancelled()) {
      Function f = it.next(); n++;
      boolean lib = f.isThunk() || f.getName().startsWith("_") || f.isExternal();
      csv.println(f.getEntryPoint()+","+f.getName()+","+f.getBody().getNumAddresses()+","+(lib?1:0));
      DecompileResults r = d.decompileFunction(f, 60, monitor);
      if (r!=null && r.decompileCompleted()) { c.println("// "+f.getEntryPoint()); c.println(r.getDecompiledFunction().getC()); ok++; }
      else c.println("// FAILED "+f.getEntryPoint()+" "+f.getName());
    }
    csv.close(); c.close();
    println("functions="+n+" decompiled="+ok);
  }
}
