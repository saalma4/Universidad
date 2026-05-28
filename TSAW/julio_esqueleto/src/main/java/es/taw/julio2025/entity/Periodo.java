package es.taw.julio2025.entity;

import lombok.Data;

import javax.persistence.*;
import java.util.List;

@Entity
@Data
@Table(name = "Periodo")
public class Periodo {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    private String nombre;
    private Integer inicio_ma;
    private Integer fin_ma;

    @OneToMany(mappedBy = "periodo")
    private List<Dinosaurio> dinosaurios;

    @Override
    public String toString() {
        return "Periodo[ id=" + id + " ]";
    }
}