// Export: function,address,string for every defined string referenced from code
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.util.DefinedStringIterator;
import java.io.*;
public class StringXrefs extends GhidraScript {
  public void run() throws Exception {
    PrintWriter w = new PrintWriter(new FileWriter(getScriptArgs()[0]+"/string_xrefs.tsv"));
    w.println("func_addr\tfunc_name\tstr_addr\tstring");
    FunctionManager fm = currentProgram.getFunctionManager();
    for (Data d : DefinedStringIterator.forProgram(currentProgram)) {
      String s = String.valueOf(d.getValue()).replace("\t"," ").replace("\n","\\n").replace("\r","");
      for (Reference r : getReferencesTo(d.getAddress())) {
        Function f = fm.getFunctionContaining(r.getFromAddress());
        if (f!=null) w.println(f.getEntryPoint()+"\t"+f.getName()+"\t"+d.getAddress()+"\t"+s);
      }
    }
    w.close();
  }
}
