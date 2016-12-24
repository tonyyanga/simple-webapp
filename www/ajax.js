function ajaxFetch(resourcesTag, resourcesLink) {
	// Fetch information at resourcesLink and update it to resourcesTag
	var xhttp
	if (window.XMLHttpRequest) {
		xhttp = new XMLHttpRequest();
	} else {
		// for IE6 or earlier compatibility
		xhttp = new ActiveXObject("Microsoft.XMLHTTP");
	}
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			document.getElementById(resourcesTag).innerHTML = this.responseText;
		}
	};
	xhttp.open("GET", resourcesLink, true);
	xhttp.send();
}
