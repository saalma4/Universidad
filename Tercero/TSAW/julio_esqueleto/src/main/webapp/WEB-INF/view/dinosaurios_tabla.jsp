<%@ page import="es.taw.julio2025.entity.Dinosaurio" %>
<%@ page import="java.util.List" %>
<%@ page import="es.taw.julio2025.entity.Habitat" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>

<%
    List<Dinosaurio> dinosaurios = (List<Dinosaurio>) request.getAttribute("dinosaurios");
    List<Habitat> habitats = (List<Habitat>) request.getAttribute("habitats");
    Integer habitatid = (Integer) request.getAttribute("habitatid");
    Float tamanio = (Float) request.getAttribute("tamanio");
    Float peso = (Float) request.getAttribute("peso");
%>
<head>
    <title>Dinosaurios</title>
</head>
<body>
<h1>Dinosaurios:</h1>
<form method="get" action="/">
    <label>
        Habitat:
        <select name="habitatid">
        <%
            for(Habitat habitat:habitats){
        %>
        <option <%=habitatid!=null&&habitatid.equals(habitat.getId())?"selected":""%> value="<%=habitat.getId()%>"><%=habitat.getNombre()%></option>
        <%
            }
        %>
        </select>
    </label>
    <label>
        Tamaño >
        <input type="number" name="tamanio" value="<%=tamanio!=null?tamanio:""%>">
    </label>
    <label>
        Peso <
        <input type="number" name="peso" value="<%=peso!=null?peso:""%>">
    </label>
    <button type="submit">Filtrar</button>
</form>
<table border="1">
    <tr>
        <th>Nombre</th>
        <th>Tamaño</th>
        <th>Peso</th>
        <th>Periodo</th>
        <th>Dieta</th>
        <th>Habitats</th>
        <th></th>
        <th></th>
    </tr>
    <%
    for(Dinosaurio dinosaurio : dinosaurios){
    %>
    <tr>
        <td><%=dinosaurio.getNombre()%></td>
        <td><%=dinosaurio.getTamaño_metros()%></td>
        <td><%=dinosaurio.getPeso_toneladas()%></td>
        <td><%=dinosaurio.getPeriodo().getNombre()%></td>
        <td><%=dinosaurio.getDieta().getTipo()%></td>
        <td><%=dinosaurio.getHabitatsString()%></td>
        <td><a href="/duplicar?id=<%=dinosaurio.getId()%>">Duplicar</a></td>
        <td><a href="/borrar?id=<%=dinosaurio.getId()%>">Borrar</a></td>
    </tr>
    <%
        }
    %>
</table>
</body>
</html>
