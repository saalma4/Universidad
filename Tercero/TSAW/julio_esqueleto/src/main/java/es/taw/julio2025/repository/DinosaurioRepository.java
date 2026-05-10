package es.taw.julio2025.repository;

import es.taw.julio2025.entity.Dinosaurio;
import es.taw.julio2025.entity.Habitat;
import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.List;

public interface DinosaurioRepository extends JpaRepository<Dinosaurio, Integer> {
    @Query("select d from Dinosaurio d join d.habitats h where ?1 in h and d.tamaño_metros > ?2 and  d.peso_toneladas < ?3")
    List<Dinosaurio> findALLByFilter(Habitat habitat, Float tamanio, Float peso, Sort sort);
}
