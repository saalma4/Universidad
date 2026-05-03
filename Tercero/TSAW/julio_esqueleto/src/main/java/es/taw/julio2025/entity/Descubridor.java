package es.taw.julio2025.entity;

import lombok.Data;

import javax.persistence.*;
import java.util.List;

@Entity
@Data
@Table(name = "Descubridor")
public class Descubridor {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    private String nombre;
    private Integer año_descubrimiento;

    @ManyToMany(mappedBy = "descubridores")
    private List<Dinosaurio> dinosaurios;

    @Override
    public String toString() {
        return "Descubridor[ id=" + id + " ]";
    }
}