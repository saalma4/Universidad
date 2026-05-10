package es.taw.julio2025.controller;

import es.taw.julio2025.entity.Dinosaurio;
import es.taw.julio2025.entity.Habitat;
import es.taw.julio2025.repository.DinosaurioRepository;
import es.taw.julio2025.repository.HabitatRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.ArrayList;
import java.util.List;

@Controller

public class DinosaurioController {

    @Autowired protected DinosaurioRepository dinosaurioRepository;
    @Autowired protected HabitatRepository habitatRepository;

    @GetMapping("/")
    public String doInit(@RequestParam(required = false) Integer habitatid,
                         @RequestParam(required = false) Float tamanio,
                         @RequestParam(required = false) Float peso,
                         @RequestParam(required = false) Integer editarId,
                         Model model){
        List<Dinosaurio> dinosauros;
        if(habitatid!=null && tamanio!= null && peso!= null){
            Habitat habitat = habitatRepository.findById(habitatid).get();
            dinosauros = dinosaurioRepository.findALLByFilter(habitat, tamanio, peso, Sort.by("peso_toneladas").ascending());
            String filtrado = "filtrado";
            model.addAttribute("filtrado", filtrado);
        }else{
          dinosauros  = dinosaurioRepository.findAll();
        }
        List<Habitat> habitats = habitatRepository.findAll();
        model.addAttribute("dinosaurios", dinosauros);
        model.addAttribute("habitatid", habitatid);
        model.addAttribute("tamanio", tamanio);
        model.addAttribute("peso", peso);
        model.addAttribute("habitats", habitats);
        model.addAttribute("editarId", editarId);
        return "dinosaurios_tabla";
    }

    @GetMapping("/duplicar")
    public String duplicar(@RequestParam Integer id){
        Dinosaurio dinoACopiar = dinosaurioRepository.findById(id).get();
        Dinosaurio dinoNuevo = new Dinosaurio();
        dinoNuevo.setDescubridores(new ArrayList<>(dinoACopiar.getDescubridores()));
        dinoNuevo.setNombre(dinoACopiar.getNombre()+"(1)");
        dinoNuevo.setHabitats(new ArrayList<>(dinoACopiar.getHabitats()));
        dinoNuevo.setDieta(dinoACopiar.getDieta());
        dinoNuevo.setPeso_toneladas(dinoACopiar.getPeso_toneladas());
        dinoNuevo.setTamaño_metros(dinoACopiar.getTamaño_metros());
        dinoNuevo.setPeriodo(dinoACopiar.getPeriodo());
        dinosaurioRepository.save(dinoNuevo);

        return "redirect:/";
    }
    @GetMapping("/borrar")
    public String doBorrar(@RequestParam Integer id){
        Dinosaurio dinosaurio = dinosaurioRepository.findById(id).get();
        dinosaurioRepository.delete(dinosaurio);
        return "redirect:/";
    }

    @PostMapping("/editar")
    public String doEditar(@RequestParam(required = false) String nombre,
                           @RequestParam(required = false) List<Integer> habitats,
                           @RequestParam(required = false) Integer id){
        Dinosaurio dinosaurio = dinosaurioRepository.findById(id).get();
        dinosaurio.setNombre(nombre);
        if(habitats!=null && !habitats.isEmpty()){
            List<Habitat> listaHabitats = habitatRepository.findAllById(habitats);
            dinosaurio.setHabitats(listaHabitats);
        }else{
            dinosaurio.setHabitats(new ArrayList<>());
        }
        dinosaurioRepository.save(dinosaurio);

        return "redirect:/";
    }
}
