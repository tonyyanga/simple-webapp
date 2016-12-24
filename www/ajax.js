function ajaxFetch(resourcesTag, resourcesLink) {
	// Fetch information at resourcesLink and update it to resourcesTag
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			document.getElementById(resourcesTag).innerHTML = this.responseText;
		}
	};
	xhttp.open("GET", resourcesLink, true);
	xhttp.send();
}
